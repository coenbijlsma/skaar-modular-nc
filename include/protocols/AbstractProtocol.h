/**
 * @file AbstractProtocol.h
 * @brief Abstraction for a chatnet protocol like irc (RFC1459)
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

#ifndef ABSTRACTPROTOCOL_H
#define ABSTRACTPROTOCOL_H

#include <string>
#include <vector>
#include "AbstractMessage.h"
//#include "AbstractAction.h"
#include "SessionInfo.h"

using namespace std;

class AbstractProtocol {
public:
	virtual ~AbstractProtocol(){}
	
	/*
	 * Returns a vector containing the registered
	 * messages for this protocol.
	 */
	virtual vector<string> registeredMessages() =0;
	
	/*
	 * Registers a message to this protocol.
	 * Returns true if this succeeded, and false
	 * if it doesn't (for example, if the message
	 * already is registered).
	 */
	virtual bool registerMessage(string message) =0;
	
	/*
	 * Unregisters the provided message at this protocol.
	 * Returns true if that succeeded, and false otherwise.
	 */
	virtual bool unregisterMessage(string message) =0;
	
	/*
	 * Returns whether the provided message is 
	 * registered at this protocol.
	 */
	virtual bool isRegisteredMessage(string message) =0;
	
	/*
	 * Tries to translate a raw string from the SkaarSocket
	 * to a decent AbstractMessage. 
	 * Returns the AbstractMessge* on success, and 
	 * (AbstractMessage*)0 if it fails.
	 */
	virtual AbstractMessage* translateIncoming(string raw) =0;
	
	/*
	 * Returns a string formatted following this protocol.
	 * The raw string is supposed to be the user input,
	 * so this is actually the way to translate user input
	 * and send it awayyyyy.
	 */
	virtual string toProtocolString(SessionInfo* sessionInfo, string raw) =0;
	
	/*
	 * Returns the sequence of strings to be sent to the server that serves
	 * this protocol, in order to register successfully. 
	 * Each string in the vector is then translated to an AbstractMessage
	 * and sent to the server.
	 * The messages are sent in the order they are in the vector, so make
	 * sure that you place them right.
	 * For an example of a register sequence, you can have a look at the 
	 * implementation of this method in the RFC1459 protocol.
	 */
	virtual vector<string> getRegisterSequence(SessionInfo* sessionInfo) =0;
	
	/*
	 * Returns the message separator for this protocol
	 */
	virtual string getMessageSeparator() =0;
};

#endif
