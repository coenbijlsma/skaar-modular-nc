#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "SkaarCallbackHandler.h"

using std::string;
using std::vector;

class AbstractAction {
public:

	virtual ~AbstractAction() {}
	
	virtual string getName() =0;
	
	virtual vector<string> getParams() =0;
	
	virtual void setCallbackHandler(SkaarCallbackHandler* handler) =0;
	
	virtual bool execute() =0;
};

#endif /* ABSTRACTACTION_H */
