#ifndef EXITACTION_H
#define EXITACTION_H

#include "AbstractAction.h"

using std::string;

class ExitAction : public AbstractAction {
public:
	ExitAction(string name, string params, SkaarCallbackHandler* handler);
	virtual ~ExitAction();
	
	string getName();
	
	void setCallbackHandler* handler(SkaarCallbackHandler* handler);
	
	bool execute();
};

#endif /* EXITACTION_H */
