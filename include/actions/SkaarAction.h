#ifndef SKAARACTION_H
#define SKAARACTION_H

class SkaarAction {
public:

	virtual ~SkaarAction() {}
	
	virtual void setCallbackHandler(CallbackHandler* handler);
	
	virtual bool execute();
};

#endif /* SKAARACTION_H */
