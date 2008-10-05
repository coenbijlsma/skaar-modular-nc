#include "Skaar.h"
#include "SkaarUser.h"
#include "Screen.h"
#include "NCursesInputReader.h"
#include "TerminalInputReader.h"
#include "TerminalGUI.h"
#include "CommandFactory.h"
#include "AbstractCommand.h"
#include "AbstractProtocol.h"
#include "RFC1459.h"

#include <iostream> // testing
#include <pthread.h>
#include <vector>

/*******************************************************************************
 *			     PRIVATE FUNCTIONS										       *
 ******************************************************************************/
void Skaar::_init(){
	/* Create a logfile */
	_log = new SkaarLog("skaar.log");

	/* BEWARE! THIS IS A VERY UGLY HACK FOR TESTING PURPOSES ONLY!*/
	_protocols["rfc1459"] = (AbstractProtocol*)new RFC1459();
	
	SkaarConfig* config = new SkaarConfig("skaar.conf");
		
	SkaarUser* user = new SkaarUser(config->getValue("core", "realname")
					, config->getValue("core", "nick")
					, config->getValue("core", "password"));
	
	
	/* Setup the session-info */
	_sessionInfo = new SessionInfo(user, config);
	
	/* Initialize the UI */
	if(_sessionInfo->getConfig()->getValue("core", "defaultui") == "ncurses"){
		initscr();
		cbreak();
		// noecho();

		if(_sessionInfo->addWindow(new Screen("foo"))){
			AbstractGUI* gui = _sessionInfo->getWindowAt(0);
			_sessionInfo->setInputReader( (AbstractInputReader*)new NCursesInputReader());
		}else{
			// log it
		}
	}else{
		if(_sessionInfo->addWindow(new TerminalGUI("foo"))){
			AbstractGUI* gui = _sessionInfo->getWindowAt(0);
			_sessionInfo->setInputReader( (AbstractInputReader*)new TerminalInputReader());
		}else{
			// log it
		}
	}
	
	/* Get the GUI and put some welcome-test in it.*/
	// XXX put that in a config file
	AbstractGUI* gui = _sessionInfo->getWindowAt(0);
	gui->addContent("Welcome to Skaar.\n type /connect <server> [<port> [proto=rfc1459]] to connect.\n");
	gui->setReceiver(_sessionInfo->getUser()->getNick());
	gui->setServer("NONE");
	gui->setActive(true);
	_sessionInfo->getInputReader()->setActive(true);
	_createThreads();
}

AbstractProtocol* Skaar::_findProtocol(string name){
	map<string, AbstractProtocol*>::iterator it = _protocols.find(name);
	
	if(it == _protocols.end()){
		return (AbstractProtocol*)0;
	}
	
	return (*it).second;
}

SkaarSocket* Skaar::_findSocket(string server){
	map<string, SkaarSocket*>::iterator it = _connections.find(server);
	
	if(it == _connections.end()){
		return (SkaarSocket*)0;
	}
	
	return (*it).second;
}

// XXX Not all messages have to be shown on the screen
void Skaar::_hndSocketInput(){
	// XXX this while(true)
	while(_continueListening){
		for(map<string, SkaarSocket*>::iterator it = _connections.begin(); it != _connections.end(); it++){
			SkaarSocket* sock = it->second;
			AbstractProtocol* proto = _findProtocol(sock->getProtocol());
			
			if(proto == 0){
				continue;
			}
			
			if(sock->pollConnection() > 0){
				// There is data, so do something about that
				string rawmsg = sock->readMessage(proto->getMessageSeparator());
				
				if(rawmsg.length() > 0){
					AbstractProtocol* proto = _findProtocol(sock->getProtocol());
					// XX replace this by _protocols.find()
					
					if(proto == 0){
						// log it and present the error to the user
						throw string("Unsupported protocol: ") + sock->getProtocol();
					}
					AbstractMessage* msg = proto->translateIncoming(rawmsg);
					
					/* 
					 * Try to find the correct window, otherwise print the output to
					 * the screen at(0)
					 */
					
					string receiver("");
					if(msg != 0){
						receiver  = msg->getSenderNick();
					}
					AbstractGUI* gui;
					
					if(receiver.length() == 0){
						/*
						 * Redirect messages without a specific receiver to the screen for the
						 * current user logged in.
						 */
						gui = _sessionInfo->getWindowFor(_sessionInfo->getUser()->getNick());
					}else{
						gui = _sessionInfo->getWindowFor(receiver);
					}
					
					if(gui == 0){
						// Create a new window if the receiver doesn't exist
						gui = _sessionInfo->getWindowAt(_sessionInfo->getWindowCount());
						gui->setReceiver(receiver);
						gui->setServer(sock->getHost());
						
						// Temporary solution, to replaced by a decent statusbar
						AbstractGUI* usergui = _sessionInfo->getWindowFor(_sessionInfo->getUser()->getNick());
						string infotext("[INFO] A new window has been opened for ");
						infotext.append(receiver);
						infotext.append("\n");
						usergui->addContent(infotext);
					}
					
					if(msg != 0){
						gui->addContent(msg->format(""));
					}else{
						_log->append("Adding message " + rawmsg + " to gui");
						_log->save();
						gui->setLog(_log);
						gui->addContent(rawmsg);
					}
					
				} /* if(rawmsg.length() > 0) */
				
			} /* if(sock->pollConnection > 0) */
			
		} /* for( connections.size() etc. )... */
		
	} /* while(true) */
}

// XXX When commands are implemented, look for them over here
void Skaar::_hndScreenOutput(){
	while(_continueListening){
		string line = _sessionInfo->getInputReader()->readLine();
		string server = _sessionInfo->getActiveWindow()->getServer();
		
		// First, check if it's a command
		_log->append(line);
		_log->save();
		AbstractCommand* cmd = CommandFactory::translate(_log, line);
		AbstractGUI* statuswindow = _sessionInfo->getWindowAt(0);
		
		if(statuswindow == 0){
			_log->append("no statuswindow");
			_log->save();
		}
		
		if(cmd == 0){
			_log->append("No command found");
			_log->save();
			// Yeah, it's a message!
			SkaarSocket* sock = _findSocket(server);
			if(sock == 0){
				continue;
			}
			
			AbstractProtocol* proto = _findProtocol(sock->getProtocol());
			if(proto == 0){
				continue;
			}
			
			string message = proto->toProtocolString(_sessionInfo, line);
			if( ! sock->sendMessage(message)){
				string fail("Could not send message " + line);
				_log->append(fail);
				fail.append(1, '\n'); // <-- fix this ugly \n
				statuswindow->addContent(fail);
			}else{
				_log->append("Message sent: " + message);
			}
			_log->save();
		}else{
			// We have a command
			cmd->setCommandHandler(this);
			if( ! cmd->execute()){
				string fail("Could not execute command " + cmd->getCommand());
				_log->append(fail);
				fail.append(1, '\n');
				statuswindow->addContent(fail);
				_log->save();
			}else{
				_log->append("Executing command successful! (command is " + line + ")");
				_log->save();
			}
		}
	} /* while(true) */
}
 
Skaar::Skaar(){
	_continueListening = true;
	_init();
}

Skaar::~Skaar(){
	endwin();
	delete _sessionInfo;
	delete _log;
}

void Skaar::_createThreads(){
	pthread_t input, output;
	int iret, oret;
	
	iret = pthread_create(&input, NULL, Skaar::_c_hndSocketInput, (void*)this);
	oret = pthread_create(&output, NULL, Skaar::_c_hndScreenOutput, (void*)this);
	
	pthread_join( input, NULL);
	pthread_join( output, NULL);
}

void* Skaar::_c_hndSocketInput(void* ptr){
	Skaar* s = (Skaar*)ptr;
	s->_hndSocketInput();
}

void* Skaar::_c_hndScreenOutput(void* ptr){
	Skaar* s = (Skaar*)ptr;
	s->_hndScreenOutput();
}

/*******************************************************************************
 *			     			PUBLIC FUNCTIONS							       *
 ******************************************************************************/

SessionInfo* Skaar::getSessionInfo(){
	return _sessionInfo;
}

bool Skaar::registerAtConnection(SkaarSocket* sock){
	// first, check of the socket already exists
	if( _connections.find(sock->getProtocol()) != _connections.end()){
		return true;
		// XXX log that you are already registered
	}
	
	if( ! sock->connected()){
		if( ! sock->createConnection() ){
			_log->append("Could not create new connection");
			_log->save();
			return false;
			// XXX log it
		}
	}
	
	// Find the protocol
	AbstractProtocol* proto = _findProtocol(sock->getProtocol());
	
	if(proto == 0){
		_log->append("Protocol not found");
		_log->save();
		return false;
		// XXX log it
	}
	
	vector<string> regsequence = proto->getRegisterSequence(_sessionInfo);

	for(int i = 0; i < regsequence.size(); i++){	
		if( ! sock->sendMessage(regsequence.at(i)) ){
			_log->append("Could not send message " + regsequence.at(i));
			_log->save();
			return false;
			// XXX log it
		}
	}
	
	// finally, add the socket to the list.
	_connections[sock->getProtocol()] = sock;
	return true;
}

