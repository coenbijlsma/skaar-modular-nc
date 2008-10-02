#include <iostream>
#include "TerminalInputReader.h"

TerminalInputReader::TerminalInputReader(){}

TerminalInputReader::~TerminalInputReader(){}

char TerminalInputReader::read(){
	char c;
	cin >> c;
	return c;
}

string TerminalInputReader::readLine(){
	string s;
	char c;
	
	while(c != _NEWLINE){
		char c;
		cin >> c;
		s.append(1, c);
	}
	return s;
}

string TerminalInputReader::read(string delim){
	string s;
	
	while(true){
		if(s.length() >= delim.length()){
			if(s.substr(s.length() - delim.length()) == delim){
				return s.substr(0, s.length() - delim.length());
			}
		}
		char c;
		cin >> c;
		s.append(1, c);
	}
	
	return s;
}

void TerminalInputReader::setActive(bool active){
	// bogus
}
