/**
 * @file AbstractInputReader.h
 * @brief Abstraction to read input from an AbstractGUI.
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

#ifndef ABSTRACTINPUTREADER_H
#define ABSTRACTINPUTREADER_H

#include <string>

using namespace std;

class AbstractInputReader {

public:
	
	/*
	 * Destructor
	 */
	virtual ~AbstractInputReader() {}
	
	/*
	 * Reads one char from the input
	 */
	virtual char read() =0;
	
	/*
	 * Reads a line from the input.
	 * See the implementation class for more
	 * details on this.
	 */
	virtual string readLine() =0;
	
	/*
	 * Reads a string from the input until
	 * delim occurs.
	 */
	virtual string read(string delim) =0;
	
	/*
	 * @brief (de)activates the inputreader.
	 * Deactivating it only means that it's
	 * possible for the InputReader to vanish
	 * into the background.
	 */
	virtual void setActive(bool active) =0;
};

#endif /* ABSTRACTINPUTREADER_H */
