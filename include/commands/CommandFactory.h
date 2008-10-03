#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "AbstractCommand.h"
#include "SkaarLog.h"

using namespace std;

class CommandFactory {
public:
	static AbstractCommand* translate(SkaarLog* log, string raw);
};

#endif /* COMMANDFACTORY_H */
