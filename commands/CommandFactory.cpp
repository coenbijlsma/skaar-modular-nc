#include "CommandFactory.h"
#include "StringTokenizer.h"
#include <ctype.h> // toupper

#include "ConnectCommand.h"
#include "ExitCommand.h"

AbstractCommand* CommandFactory::translate(SkaarLog* log, string raw){
	StringTokenizer st(raw, ' ');
	
	string command = st.next();
	if(command[0] != '/'){
		return (AbstractCommand*)0;
		// XXX log it
	}
	command = command.substr(1);
	
	for(unsigned int i = 0; i < command.size(); i++){
		command[i] = toupper(command[i]);
	}
	
	if(command.compare(ConnectCommand::COMMAND) == 0){
		return new ConnectCommand(log, raw);
	}else if(command.compare(ExitCommand::COMMAND) == 0){
		return new ExitCommand(log, raw);
	}
	return (AbstractCommand*)0;
	// XXX the rest
}
