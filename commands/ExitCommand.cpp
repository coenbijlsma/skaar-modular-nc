#include "ExitCommand.h"
#include "StringTokenizer.h"
#include "SkaarSocket.h"
#include "stringtools.h"

const string ExitCommand::COMMAND = "EXIT";

ExitCommand::ExitCommand(SkaarLog* log, string raw){
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
	
}

ExitCommand::~ExitCommand(){}

string ExitCommand::getCommand(){
	return _command;
}

void ExitCommand::setCallbackHandler(SkaarCallbackHandler* handler){
	_handler = handler;
}

bool ExitCommand::execute(){
	if(_handler == 0){
		_log->append("No handler for EXIT");
		_log->save();
		return false;
	}else{
		_handler->exit();
		return true;
	}
}
