#ifndef SKAARCOMMAND_H
#define SKAARCOMMAND_H

#include "SkaarCommandExecutue.h"

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
	
	virtual void setSkaarCommandExecutor(SkaarCommandExecutor* exe) =0;
	
};

#endif /* SKAARCOMMAND_H */
