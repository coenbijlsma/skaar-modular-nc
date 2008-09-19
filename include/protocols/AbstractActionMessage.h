/**
 * @file AbstractActionMessage.h
 * @brief Abstraction for messages that imply an action
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

#ifndef ABSTRACTACTIONMESSAGE_H
#define ABSTRACTACTIONMESSAGE_H

#include <string>
#include "AbstractMessage.h"

using namespace std;

/*
 * This class is an extra interface on top of AbstractMessage,
 * that you can use for messages that imply an action.
 * For example, sometimes when a message is received, the server expects
 * that you send back another message.
 * Another example is that a user joins a channel (in case of,
 * let's say, IRC), and the list of users must be edited to 
 * stay accurate.
 */
class AbstractActionMessage : public AbstractMessage {
public:

	virtual ~AbstactActionMessage(){}
	
	virtual string getAction() =0;
	
	virtual bool execute() =0;
};


#endif /* ABSTRACTACTIONMESSAGE_H */
