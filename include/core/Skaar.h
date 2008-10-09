#ifndef SKAAR_H
#define SKAAR_H

#include <map>

#include "AbstractProtocol.h"
#include "SessionInfo.h"
#include "SkaarConfig.h"
#include "SkaarLog.h"
#include "SkaarSocket.h"
#include "SkaarCallbackHandler.h"

using namespace std;

class Skaar : public SkaarCallbackHandler {
private:
	bool _continueListening;
	
	SkaarLog* _log;
	SessionInfo* _sessionInfo;
	map<string, SkaarSocket*> _connections;
	map<string, AbstractProtocol*> _protocols;
	void _init();
	AbstractProtocol* _findProtocol(string name);
	SkaarSocket* _findSocket(string server);
	
	/* Functions for the threads */
	void _hndSocketInput();
	void _hndScreenOutput();
	void _createThreads();
	
	static void* _c_hndSocketInput(void* ptr);
	static void* _c_hndScreenOutput(void* ptr);
public:
	Skaar();
	virtual ~Skaar();

	SessionInfo* getSessionInfo();
	
	/* Callback-methods for commands and actions */
	bool registerAtConnection(SkaarSocket* sock);
	
	void exit();
};

#endif
