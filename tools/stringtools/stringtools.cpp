#include "stringtools.h"
#include <ctype.h>

string strtoupper(string& s){
	for(int i = 0; i < s.size(); i++){
		s[i] = toupper(s[i]);
	}
	
	return s;
}

string strtolower(string& s){
	for(int i = 0; i < s.size(); i++){
		s[i] = tolower(s[i]);
	}
	
	return s;
}
