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
	Config* _config;
	SkaarLog* _log;
	SessionInfo* _sessionInfo;
	map<string, SkaarSocket*> _connections;
	map<string, AbstractProtocol*> _protocols;
	void _init();
	
	/* Functions to be used by p_thread */
	void* _hndSocketInput(void* ptr);
	void* _hndScreenOutput(void* ptr);
	
	static void* _c_hndSocketInput(void* ptr);
	static void* _c_hndScreenOutput(void* ptr);
	
	void _createThreads();
	
	
public:
	Skaar();
	virtual ~Skaar();
	
};

#endif
