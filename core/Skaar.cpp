#include "Skaar.h"
#include "SkaarUser.h"
#include "Screen.h"
#include "NCursesInputReader.h"
#include "TerminalInputReader.h"
#include "TerminalGUI.h"
#include "CommandFactory.h"
#include "AbstractCommand.h"

#include <iostream> // testing
#include <pthread.h>
#include <vector>

/*******************************************************************************
 *			     PRIVATE FUNCTIONS										       *
 ******************************************************************************/
void Skaar::_init(){
	/* Create a logfile */
	_log = new SkaarLog("skaar.log");

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

		Screen* scr = new Screen("foo");
		_sessionInfo->setInputReader(new NCursesInputReader());
		if(_sessionInfo->addWindow(scr)){
			// log it
		}else{
			// log it
		}
	}else{
		TerminalGUI* tgui = new TerminalGUI("foo");
		_sessionInfo->setInputReader(new TerminalInputReader());
		if(_sessionInfo->addWindow(tgui)){
			// log it
		}else{
			// log it
		}
	}
	
	/* Get the GUI and put some welcome-test in it.*/
	// XXX put that in a config file
	AbstractGUI* gui = _sessionInfo->getWindowAt(0);
	gui->addContent("Welcome to Skaar.\n type /connect <server> [<port> [proto=rfc1459]] to connect.\n");
	gui->setReceiver(_sessionInfo->getUser()->getNick());
	gui->setActive(true);
	_createThreads();
	
}

AbstractProtocol* Skaar::_findProtocol(string name){
	map<string, AbstractProtocol*>::iterator it = _protocols.find(name);
	
	if(it = _protocols.end()){
		return (AbstractProtocol*)0;
	}
	
	return (*it).second;
}

// XXX Not all messages have to be shown on the screen
void Skaar::_hndSocketInput(){
	// XXX this while(true)
	while(_continueListening){
		for(map<string, SkaarSocket*>::iterator it = _connections.begin(); it != _connections.end(); it++){
			SkaarSocket* sock = it->second;
			
			if(sock->pollConnection() > 0){
				// There is data, so do something about that
				string rawmsg = sock->readMessage();
				
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
					string receiver = msg->getSenderNick();
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
					
					gui->addContent(msg->format(""));
					
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
		SkaarSocket* sock = _connections[server];
		AbstractGUI* fist = _sessionInfo->getWindowAt(0); // for printing statusmessages
				
		if(sock == 0){
			continue;
		}
		AbstractProtocol* proto = _protocols[sock->getProtocol()];
		
		if(proto == 0){
			continue;
		}
		
		string msg = proto->toProtocolString(_sessionInfo, line);
		
		if(msg.length() == 0){
			// Check if maybe it's a command
			AbstractCommand* cmd = CommandFactory::translate(line);
			
			if(cmd == 0){
				continue;
			}
			cmd->setCommandHandler(this);
			if( ! cmd->execute()){
				string failcmd("Executing command failed for command ");
				failcmd.append(line);
				failcmd.append(1, '\n');
				
				first->addContent(failcmd);
			}
			
		}else if( ! sock->sendMessage(msg) ){
			string failmsg("Could not send message ");
			failmsg.append(line);
			failmsg.append(1, '\n');
			
			first->addContent(failmsg);
		}
	} /* while(true) */
}
 
Skaar::Skaar(){
	_init();
}

Skaar::~Skaar(){
	endwin();
	delete _sessionInfo;
	delete _config;
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

static void* Skaar::_c_hndSocketInput(void* ptr){
	Skaar* s = (Skaar*)ptr;
	s->_hndSocketInput();
}

static void* Skaar::_c_hndScreenOutput(void* ptr){
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
			return false;
			// XXX log it
		}
	}
	
	// Find the protocol
	AbstractProtocol* proto = _findProtocol(sock->getProtocol());
	
	if(proto == 0{
		return false;
		// XXX log it
	}
	
	vector<string> regsequence = proto->getRegisterSequence(_sessionInfo);

	for(int i = 0; i < regsequence.size(); i++){	
		if( ! sock->sendMessage(regsequence.at(i)) ){
			return false;
			// XXX log it
		}
	}
	
	// finally, add the socket to the list.
	_connections[sock->getProtocol()] = sock;
	return true;
}

