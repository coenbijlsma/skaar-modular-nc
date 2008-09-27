#include "ConnectCommand.h"
#include "StringTokenizer.h"
#include "SkaarSocket.h"

ConnectCommand::ConnectCommand(string raw){
}

ConnectCommand::~ConnectCommand(){}

string ConnectCommand::getCommand(){
	return _command;
}

void ConnectCommand::setCommandHandler(CommandHandler* handler){
	_handler = handler;
}

bool ConnectCommand::execute(){
	if(_port == 0 || _proto.size() == 0){
		string configport = _handler->getSessionInfo->getConfig()->getValue("servers", _server);
		
		if(configport.size() == 0){
			return false;
			// XXX log it
		}
		_port = atoi(configport.c_str());
		_proto = _handler->getSessionInfo->getConfig()->getValue("protocols", _server);
		
		if(_proto.size() == 0){
			return false;
			// XXX log it
		}
	}
	
	SkaarSocket* newsock = new SkaarSocket(_server.c_str(), _port, _proto);
	
	if(newsock == 0){
		return false;
		// XXX log it
	}
	
	if( ! _handler->registerAtConnection(newsock)){
		delete newsock;
		return false;
		// XXX log it
	}
	return true;
}
