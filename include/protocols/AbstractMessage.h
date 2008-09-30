/**
 * @file AbstractMessage.h
 * @brief Abstraction for messages of any protocol
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

#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include "AbstractProtocol.h"
#include <string>
#include <vector>

using namespace std;

class AbstractProtocol;

class AbstractMessage {
public:
	virtual ~AbstractMessage(){}
	
	/*
	 * Returns the prefix that belongs to this
	 * message, if any.
	 * If no prefix is available, this method
	 * should return an empty string.
	 */
	virtual string getPrefix() =0;
	
	/*
	 * Returns the nick of the sender of 
	 * the message.
	 */
	virtual string getSenderNick() =0;
	
	/*
	 * Returns the receiver of the message.
	 * If no receiver is present, this method
	 * returns an empty string.
	 */
	virtual string getReceiver() =0;
	
	/*
	 * Returns the command of this message, 
	 * say PRIVMSG
	 */
	virtual string getCommand() =0;
	
	/*
	 * Returns the minimum amount of parameters
	 * required for this message.
	 */
	virtual unsigned int minParams() =0;
	
	/*
	 * Returns a string formatted according to the
	 * given format string.
	 * XXX The format should be: ...
	 */
	virtual string format(string format) =0;
	
	/*
	 * Returns the parameters that go with the message.
	 */
	virtual vector<string> getParams() =0;
	
	/*
	 * Returns the protocol this message belongs to.
	 */
	virtual AbstractProtocol* getProtocol() =0;
	
};

#endif
