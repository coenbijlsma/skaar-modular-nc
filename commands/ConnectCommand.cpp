#include "ConnectCommand.h"
#include "StringTokenizer.h"
#include "SkaarSocket.h"
#include "stringtools.h"

const string ConnectCommand::COMMAND = "CONNECT";

ConnectCommand::ConnectCommand(SkaarLog* log, string raw){
	StringTokenizer st(raw, ' ');
	string command = st.next();
	_log = log;
	
	if(command[0] != '/'){
		string fail("Not a command: ");
		fail.append(raw);
		throw fail;
	}else{
		command = command.substr(1);
	}
	
	strtoupper(command);
	_command = command;
	
	if(st.count() > (MAXPARAMS +1)){
		throw string("Too many parameters in connect command.");
	}
	if(st.count() == MINPARAMS){
		// the command itself also counts in st.count()
		throw string("Not enough parameters in connect command");
	}
	
	_server = st.next();
	
	if(st.hasNext()){
		_port = atoi( (st.next()).c_str());
	}else{
		_port = 0;
	}
	if(st.hasNext()){
		_proto = st.next();
	}else{
		_proto = "rfc1459";
	}
}

ConnectCommand::~ConnectCommand(){}

string ConnectCommand::getCommand(){
	return _command;
}

void ConnectCommand::setCallbackHandler(SkaarCallbackHandler* handler){
	_handler = handler;
}

bool ConnectCommand::execute(){
	if(_handler == 0){
		_log->append("No handler for CONNECT");
		_log->save();
		return false;
	}
	
	if(_port == 0 || _proto.size() == 0){
		string configport = _handler->getSessionInfo()->getConfig()->getValue("servers", _server);
		
		if(configport.size() == 0){
			_log->append("No port defined for CONNECT");
			_log->save();
			return false;
		}
		_port = atoi(configport.c_str());
		_proto = _handler->getSessionInfo()->getConfig()->getValue("protocols", _server);
		_log->append("server " + _server + " has protocol " + _proto);
		_log->save();
		if(_proto.size() == 0){
			_log->append("No protocol found");
			_log->save();
			return false;
		}
	}
	
	SkaarSocket* newsock = new SkaarSocket(const_cast<char*>(_server.c_str()), _port, _proto);
	
	if(newsock == 0){
		_log->append("No socket created for CONNECT");
		_log->save();
		return false;
	}
	
	if( ! _handler->registerAtConnection(newsock)){
		delete newsock;
		_log->append("Could not register at connection");
		_log->save();
		return false;
	}
	return true;
}
