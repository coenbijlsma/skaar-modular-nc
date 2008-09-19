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
	string _name;
	string _realName;
	int _flags;

public:
	static const int NO_FLAGS = 0;
	static const int INVISIBLE = 1;
	static const int SERVER_NOTICES = 2;
	static const int WALLOPS = 4;
	static const int OPERATOR = 8;
	
	RFC1459User(string name, string realname, int flags);
	~RFC1459User();
	
	string getName();
	
	string getRealName();
	
	int getFlags();
	
	void setFlag(int flag, bool enabled);
	
	bool hasFlag(int flag);
	
};

#endif /* RFC1459USER_H */
