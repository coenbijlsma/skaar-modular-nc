#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "AbstractCommand.h"

using namespace std;

class CommandFactory {
public:
	static AbstractCommand* translate(string raw);
};

#endif /* COMMANDFACTORY_H */
