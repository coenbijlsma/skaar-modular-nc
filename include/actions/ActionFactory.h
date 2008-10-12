#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "AbstractAction.h"
#include "SkaarCallbackHandler.h"

class ActionFactory {
public:

	static AbstractAction* create(std::string name, SkaarCallbackHandler* handler);
};

#endif /* ACTIONFACTORY_H */
