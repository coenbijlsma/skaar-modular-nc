#ifndef SKAAR_H
#define SKAAR_H

#include <map>

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
	
	void _init();
	
public:
	Skaar();
	virtual ~Skaar();
	
};

#endif
