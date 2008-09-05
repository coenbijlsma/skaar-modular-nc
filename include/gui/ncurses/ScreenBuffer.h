#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <string>
#include <vector>

/*
 * Since: 2008-09-04
 * Author: Coen Bijlsma
 * License: GPLv3
 * See also: Screen.h, man 3 WINDOW
 *
 * This class serves as a buffer for a Screen. In short, a Screen
 * is a virtual screen that can write data to a WINDOW* (man 3 WINDOW).
 */
 
using namespace std;

class ScreenBuffer {
private:

	/*
	 * The maximum amount of lines in the buffer. If set to the 
	 * default (-1), the mamimum number of lines is equal to 
	 * vector.max_size().
	 */
	int _maxlines; 
	
	/* Contains the lines for the Screen */
	vector<string> _lines;
	
public:
	ScreenBuffer(int maxlines = -1);
	~ScreenBuffer();
	
	/* Adds a line to the buffer */
	void put(string line);
	
	/* 
	 * Returns the line at position linepos, or an
	 * empty string if the linepos doesn't exist.
	 */
	string get(int linepos);
	
	/*
	 * Returns all the lines contained in the buffer.
	 */
	vector<string> getAll();
	
	/* Overloaded operators */
	ScreenBuffer& operator<<(string s);
	ScreenBuffer& operator<<(const char* c);
	ScreenBuffer& operator+(string s);
	ScreenBuffer& operator+(const char* c);
};

#endif
