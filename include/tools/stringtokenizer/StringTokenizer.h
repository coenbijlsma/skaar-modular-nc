#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

class StringTokenizer {
private:
	char* _sequence;
	char _delimeter;
	
	int _currentLoc;
	int _count;
	char* _currentToken;
	char* _nextToken;

public:
	StringTokenizer(string seq, char delim);
	virtual ~StringTokenizer();
	
	bool hasNext();
	int count();
	string next();
};

#endif
