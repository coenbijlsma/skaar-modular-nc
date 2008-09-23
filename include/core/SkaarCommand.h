#ifndef SKAARCOMMAND_H
#define SKAARCOMMAND_H

using namespace std;

class SkaarCommand {

public:
	
	virtual ~SkaarCommand(){}
	
	/*
	 * Performs the necessary actions needed
	 * to carry out the command successfully.
	 *
	 * Returns true on success, false on failure.
	 */
	virtual bool execute() =0;
	
	/*
	 * Sets the SessionInfo that can be used by this command,
	 * to alter some parameters, or whatever the command
	 * is supposed to do.
	 * It's important that you call this method *before* the
	 * call to SkaarCommand::execute() is made, because the command
	 * could fail if it has no access to the sessions' information.
	 * Another option is to add the SessionInfo to the constructor 
	 * as an mandatory parameter.
	 */
	virtual void setSessionInfo(SessionInfo* info) =0;
};

#endif /* SKAARCOMMAND_H */
