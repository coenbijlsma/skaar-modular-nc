#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "SkaarSocket.h"
#include "SessionInfo.h"

using namespace std;

class CommandHandler {
public:
	virtual ~CommandHandler(){}
	
	virtual SessionInfo* getSessionInfo() =0;
	
	virtual bool registerAtConnection(SkaarSocket* sock) =0;
	
};

#endif /* COMMANDHANDLER_H */
