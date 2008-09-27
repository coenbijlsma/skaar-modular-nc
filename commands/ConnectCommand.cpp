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
		string configport = _info->getConfig()->getValue("servers", _server);
		
		if(configport.size() == 0){
			return false;
		}
		_port = atoi(configport.c_str());
		_proto = _info->getConfig()->getValue("protocols", _server);
		
		
		
}
