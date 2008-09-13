/**
 * @file TerminalInputReader.h
 * @brief The InputReader for TerminalGUI.
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

#ifndef TERMINALINPUTREADER_H
#define TERMINALINPUTREADER_H

#include <string>

using namespace std;

class TerminalInputReader {
private:
	static const char _NEWLINE = '\n';
	
public:
	
	TerminalInputReader();
	~TerminalInputReader();
	
	char read();
	string readLine();
	string read(string delim);
	
};

#endif /* TERMINALINPUTREADER_H */
