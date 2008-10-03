#include "CommandFactory.h"
#include "StringTokenizer.h"
#include <ctype.h> // toupper

#include "ConnectCommand.h"

AbstractCommand* CommandFactory::translate(SkaarLog* log, string raw){
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
	
	log->append("'" + command + "'");
	log->save();
	if(command.compare(ConnectCommand::COMMAND) == 0){
		return new ConnectCommand(raw);
	}
	return (AbstractCommand*)0;
	// XXX the rest
}
