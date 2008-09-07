#include "Skaar.h"
#include "SkaarUser.h"
#include "Screen.h"
#include "TerminalGUI.h"
#include <iostream> // testing

/*******************************************************************************
 * 							PRIVATE FUNCTIONS								   *
 ******************************************************************************/
void Skaar::_init(){
	/* Read the config */
	_config = new Config("skaar.conf");
	
	/* Create a logfile */
	_log = new SkaarLog("skaar.log");
	
	SkaarUser* user = new SkaarUser(_config->getValue("core", "realname")
									, _config->getValue("core", "nick")
									, _config->getValue("core", "password"));
	
	//cout << "Setting up sessioninfo" << endl;
	/* Setup the session-info */
	_sessionInfo = new SessionInfo(user);
	
	//cout << "Initializing UI" << endl;
	/* Initialize the UI */
	if(_config->getValue("core", "defaultui") == "ncurses"){
		cout << "ncurses UI" << endl;
		initscr();
		cbreak();
		//noecho();
		Screen* scr = new Screen("foo");
		cout << "Adding new window" << endl;
		if(_sessionInfo->addWindow(scr)){
			cout << "Succes!" << endl;
		}else{
			cout << "FAIL!" << endl;
		}
	}else{
		cout << "terminal UI" << endl;
		TerminalGUI* tgui = new TerminalGUI("foo");
		_sessionInfo->addWindow(tgui);
	}
	
	//cout << "Adding some content" << endl;
	AbstractGUI* gui = _sessionInfo->getWindowAt(0);
	gui->addContent("Welcome to Skaar.\n type /connect <server> [<port>] to connect.\n");
	gui->setActive(true);
	
}

void Skaar::_hndSocketInput(void* ptr){
	// XXX this while(true)
	while(true){
		for(map<string, SkaarSocket*>::iterator it = _connections.begin(); it != _connectiond.end(); it++){
			SkaarSocket* sock = it->second;
			
			if(sock->pollConnection() > 0){
				// There is data, so do something about that
				string rawmsg = sock->readMessage();
				
				if(rawmsg.length() > 0){
					AbstractProtocol* proto = _protocols[sock->getProtocol()];
					if(proto == 0){
						throw string("Unsupported protocol: ") + sock->getProtocol();
					}
					AbstractMessage* msg = proto->translateIncoming(rawmsg);
				} /* if(rawmsg.length() > 0) */
				
			} /* if(sock->pollConnection > 0) */
			
		} /* for( connections.size() etc. )... */
		
	} /* while(true) */

Skaar::Skaar(){
	_init();
}

Skaar::~Skaar(){
	endwin();
	delete _sessionInfo;
	delete _config;
	delete _log;
}


