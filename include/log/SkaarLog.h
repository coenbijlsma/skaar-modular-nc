#ifndef SKAARLOG_H
#define SKAARLOG_H

#include <string>
#include <vector>

using namespace std;

class SkaarLog {
private:
	string _filename;
	vector<string> _entries;
	
	void _init();
	string _getDateTime(string);

public:
	enum loglevel_t {LOG_USER = 0, LOG_INFO, LOG_NOTICE, LOG_WARNING, LOG_ERROR, LOG_FAILURE};
	
	SkaarLog();
	
	SkaarLog(string);
	
	~SkaarLog();
	
	void append(string log, loglevel_t severity = LOG_USER);
	
	void append(const char* log, loglevel_t severity = LOG_USER);
	
	bool save();
	
};

#endif /* SKAARLOG_H */
