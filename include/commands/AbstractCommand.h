#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include "CommandHandler.h"
#include <string>

using namespace std;

class AbstractCommand {
public:
	virtual ~AbstractCommand(){}
	
	virtual string getCommand() =0;
	
	virtual void setCommandHandler(CommandHandler* handler) =0;
	
	virtual bool execute() =0;
};

#endif /* ABSTRACTCOMMAND_H */
