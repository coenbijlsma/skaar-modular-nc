#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(unsigned int maxlines){
	_maxlines = maxlines;
}

ScreenBuffer::~ScreenBuffer(){
	_lines.clear();
}

void ScreenBuffer::put(string line){
	_lines.push_back(line);
}

/* zero-based linepos */
string ScreenBuffer::get(unsigned int linepos){
	if( (linepos > (_maxlines -1)) || linepos > _lines.size() ){
		return string("");
	}
	
	return _lines.at(linepos);
}

vector<string> ScreenBuffer::getAll(){
	return _lines;
}

ScreenBuffer& ScreenBuffer::operator<<(string s){
	put(s);
	return *this;
}

ScreenBuffer& ScreenBuffer::operator<<(const char* c){
	put(string(c));
	return *this;
}

ScreenBuffer& ScreenBuffer::operator+(string s){
	put(s);
	return *this;
}

ScreenBuffer& ScreenBuffer::operator+(const char* c){
	put(string(c));
	return *this;
}
