/**
 * @file RFC1459User.h
 * @brief Implementation of an user in the RFC1459.
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

#ifndef RFC1459USER_H
#define RFC1459USER_H

#include <string>

using namespace std;

class RFC1459User {
private:
	static const string _ALLOWED_FLAGS = "iwso";
	string _nick;
	string _realName;
	string _flags;

	boolean _isLegal(char flag);
public:
	static const char NO_FLAGS = '\0';
	static const char INVISIBLE = 'i';
	static const char SERVER_NOTICES = 's';
	static const char WALLOPS = 'w';
	static const char OPERATOR = 'o';
	
	RFC1459User(string name, string realname, string flags);
	~RFC1459User();
	
	string getNick();
	
	string getRealName();
	
	string getFlags();
	
	void setFlag(char flag, bool enabled);
	
	bool hasFlag(char flag);
	
};

#endif /* RFC1459USER_H */
