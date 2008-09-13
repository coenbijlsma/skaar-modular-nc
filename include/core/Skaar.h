#ifndef SKAAR_H
#define SKAAR_H

#include <map>

#include "AbstractProtocol.h"
#include "SessionInfo.h"
#include "Config.h"
#include "SkaarLog.h"
#include "SkaarSocket.h"

using namespace std;

class Skaar {
private:
	bool _continueListening;
	
	Config* _config;
	SkaarLog* _log;
	SessionInfo* _sessionInfo;
	map<string, SkaarSocket*> _connections;
	map<string, AbstractProtocol*> _protocols;
	void _init();
	
	/* Functions for the threads */
	void _hndSocketInput();
	void _hndScreenOutput();
	void _createThreads();
	
	static void* _c_hndSocketInput(void* ptr);
	static void* _c_hndScreenOutput(void* ptr);
public:
	Skaar();
	virtual ~Skaar();
	
};

#endif
