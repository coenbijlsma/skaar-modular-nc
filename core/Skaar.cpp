#include "Skaar.h"
#include "SkaarUser.h"
#include "Screen.h"
#include "NCursesInputReader.h"
#include "TerminalInputReader.h"
#include "TerminalGUI.h"
#include <iostream> // testing
#include <pthread.h>

/*******************************************************************************
 *			     PRIVATE FUNCTIONS				       *
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
	gui->addContent("Welcome to Skaar.\n type /connect <server> [<port>] to connect.\n");
	gui->setReceiver(_sessionInfo->getUser()->getNick());
	gui->setActive(true);
	_createThreads();
	
}

// XXX Not all messages have to be shown on the screen
void Skaar::_hndSocketInput(){
	// XXX this while(true)
	while(_continueListening){
		for(map<string, SkaarSocket*>::iterator it = _connections.begin(); it != _connectiond.end(); it++){
			SkaarSocket* sock = it->second;
			
			if(sock->pollConnection() > 0){
				// There is data, so do something about that
				string rawmsg = sock->readMessage();
				
				if(rawmsg.length() > 0){
					AbstractProtocol* proto = _protocols[sock->getProtocol()];
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
		
		if(sock == 0){
			continue;
		}
		AbstractProtocol* proto = _protocols[sock->getProtocol()];
		
		if(proto == 0){
			continue;
		}
		
		string msg = proto->toProtocolString(_sessionInfo, line);
		
		if(msg.length() == 0){
			//XXX see if it's a SkaarCommand, otherwise continue
			continue;
		}
		
		if( ! sock->sendMessage(msg) ){
			AbstractGUI* first = _sessionInfo->getWindowAt(0);
			string fail("Could not send message ");
			fail.append(line);
			fail.append('\n');
			
			first->addContent(fail);
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
