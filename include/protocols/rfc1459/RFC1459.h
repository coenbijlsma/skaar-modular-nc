/**
 * @file RFC1459.h
 * @brief Implementation of the RFC1459 protocol (IRC)
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

#ifndef RFC1459_H
#define RFC1459_H

#include <string>
#include <vector>
#include "AbstractProtocol.h"
#include "AbstractMessage.h"
#include "RFC1459Channel.h"

using namespace std;

class RFC1459 : public AbstractProtocol {
private:
	vector<string> _registeredMessages;
	vector<RFC1459Channel*> _joinedChannels;
		
public:
	
	/*
	 * Constructor.
	 */
	RFC1459();
	
	/*
	 * Destructor.
	 */
	virtual ~RFC1459();
	
	/*
	 * Returns a vector that contains
	 * the commands of the messages that
	 * are currently registered.
	 * Messages have to be registered before
	 * they can be sent.
	 */
	vector<string> registeredMessages();
	
	/*
	 * Registers the provided message.
	 * Returns false if the message already
	 * is registered, and true if registration
	 * succeeded.
	 * The string should be in uppercase, 
	 * and it will be converted to uppercase
	 * if not already so.
	 */
	bool registerMessage(string message);
	
	/*
	 * Removes the provided message from the
	 * vector containing the registered messages.
	 * Returns true on succes, false if the 
	 * message wasn't registered in the first place.
	 */
	bool unregisterMessage(string message);
	
	/*
	 * Returns whether tme provided message
	 * is registered here.
	 */
	bool isRegistered(string message);
	
	/*
	 * Returns the correct AbstractMessage* for the
	 * provided raw string.
	 * If the message for the raw string hasn't been
	 * registered yet, it will be here.
	 */
	AbstractMessage* translateIncoming(string raw);
	
	/*
	 * This method does the opposite from translateIncoming(string raw).
	 * Is creates a string formatted for the RFC1459 protocol from a string
	 * that has been entered by the user.
	 */
	string toProtocolString(SessionInfo* sessionInfo, string raw);
	
	/*
	 * Adds a channel to the list of joined channels.
	 */
	void addJoinedChannel(RFC1459Channel* chan);
	
	/*
	 * Removes the specified channel from the list
	 * of joined channels and destroys it.
	 */
	void removeJoinedChannel(RFC1459Channel* chan);
	
	/*
	 * Convenience-method for removeJoinedChannel(RFC1459Channel* chan)
	 */
	void removeJoinedChannel(string name);
	
	/*
	 * Returns a sequence of string that must be sent to the server
	 * in order to register the current user.
	 */
	vector<string> getRegisterSequence(SessionInfo* sessionInfo);
};

#endif
