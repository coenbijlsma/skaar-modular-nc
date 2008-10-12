/**
 * @file ScreenBuffer.h
 * @brief buffer for a Screen
 *
 * Copyright (c) 2008 Coen Bijlsma
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <string>
#include <vector>

/*
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
	unsigned int _maxlines; 
	
	/* Contains the lines for the Screen */
	vector<string> _lines;
	
public:
	ScreenBuffer(unsigned int maxlines = 0);
	~ScreenBuffer();
	
	/* Adds a line to the buffer */
	void put(string line);
	
	/* 
	 * Returns the line at position linepos, or an
	 * empty string if the linepos doesn't exist.
	 */
	string get(unsigned int linepos);
	
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
