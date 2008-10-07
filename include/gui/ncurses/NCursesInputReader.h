/**
 * @file NCursesInputReader.h
 * @brief Used to read data from the input.
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

#ifndef NCursesInputReader_H
#define NCursesInputReader_H

#include <panel.h>
#include <string>
#include "AbstractInputReader.h"

using namespace std;

class NCursesInputReader : public AbstractInputReader {
private:
	static const char _NEWLINE = '\n';
	PANEL* _input;
	
public:
	
	/*
	 * Constructor.
	 */
	NCursesInputReader();
	
	/*
	 * Destructor.
	 */
	~NCursesInputReader();
	
	/*
	 * Reads one char from the input, and
	 * returns it afterwards. If the char
	 * equals newline (UNIX only) the window
	 * automatically scrolls up one line.
	 */
	char read();
	
	/*
	 * Reads one line from the input.
	 * XXX: Currently this only works
	 * in UNIX, WIN32 will come later.
	 * After reading the line, the window
	 * scrolls up one line.
	 */
	string readLine();
	
	/*
	 * Reads a string until delim from the
	 * input.
	 * The window does NOT scroll after a call
	 * to this method, use scroll() if you want 
	 * it to.
	 */
	string read(string delim);
	
	/*
	 * Scrolls the panel n lines. If n is positive,
	 * the window scrolls up n lines, otherwise
	 * the window scrolls down n lines.
	 * @see man 3 wscrl
	 */
	int nir_scroll(int n);
	
	/*
	 * @brief Activates the InputReader.
	 */
	void setActive(bool active);
};

#endif /* NCursesInputReader_H */
