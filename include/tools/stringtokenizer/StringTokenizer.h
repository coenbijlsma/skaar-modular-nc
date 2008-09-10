/**
 * @file StringTokenizer.h
 * @brief A class to divide and handle a string into tokens
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

	/*
	 * Constructor.
	 * Initializes the tokenizer and its tokens.
	 */
	StringTokenizer(string seq, char delim);
	
	/*
	 * Destructor.
	 * Cleans up and exits.
	 */
	virtual ~StringTokenizer();
	
	/*
	 * Returns whether there are any tokens left
	 * after the current position.
	 */
	bool hasNext();
	
	/*
	 * Returns tne amount of tokens there are
	 * in the string.
	 */
	int count();
	
	/*
	 * Returns the next token after
	 * the current position.
	 */
	string next();
};

#endif
