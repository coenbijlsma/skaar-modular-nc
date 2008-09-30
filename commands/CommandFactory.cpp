#include "CommandFactory.h"
#include "StringTokenizer.h"
#include <ctype.h> // toupper

#include "ConnectCommand.h"

AbstractCommand* CommandFactory::translate(string raw){
	StringTokenizer st(raw, ' ');
	
	string command = st.next();
	if(command[0] != '/'){
		return (AbstractCommand*)0;
		// XXX log it
	}
	command = command.substr(1);
	
	for(int i = 0; i < command.size(); i++){
		command[i] = toupper(command[i]);
	}
	
	if(command == ConnectCommand::COMMAND){
		return new ConnectCommand(raw);
	}
	return (AbstractCommand*)0;
	// XXX the rest
}
