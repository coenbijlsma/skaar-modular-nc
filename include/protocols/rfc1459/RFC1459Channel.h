/**
 * @file RFC1459Channel.h
 * @brief A representation of a channel
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

#ifndef RFC1459CHANNEL_H
#define RFC1459CHANNEL_H

#include <string>
#include <vector>
#include "RFC1459User.h"

using namespace std;

/**
 * A channel is a named group of one or more clients which will all receive 
 * messages addressed to that channel. The channel is created implicitly when
 * the first client joins it, and the channel ceases to exist when the last
 * client leaves it. While channel exists, any client can reference the channel
 * using the name of the channel.
 *
 * Channels names are strings (beginning with a '&' or '#' character) of length
 * up to 200 characters. Apart from the the requirement that the first 
 * character being either '&' or '#'; the only restriction on a channel name
 * is that it may not contain any spaces (' '), a control G (^G or ASCII 7), or
 * a comma (',' which is used as a list item separator by the protocol).
 *
 * There are two types of channels allowed by this protocol. One is a 
 * distributed channel which is known to all the servers that are connected
 * to the network. These channels are marked by the first character being a
 * only clients on the server where it exists may join it. These are
 * distinguished by a leading '&' character. On top of these two types, there
 * are the various channel modes available to alter the characteristics of
 * individual channels. See section 4.2.3 (MODE command) for more details on 
 * this.
 *
 * To create a new channel or become part of an existing channel, a user is
 * required to JOIN the channel. If the channel doesn't exist prior to joining,
 * the channel is created and the creating user becomes a channel operator.
 * If the channel already exists, whether or not your request to JOIN that
 * channel is honoured depends on the current modes of the channel. For 
 * example, if the channel is invite-only, (+i), then you may only join if
 * invited. As part of the protocol, a user may be a part of several channels
 * at once, but a limit of ten (10) channels is recommended as being ample
 * for both experienced and novice users. See section 8.13 for more information
 * on this.
 *
 * If the IRC network becomes disjoint because of a split between two servers,
 * the channel on each side is only composed of those clients which are
 * connected to servers on the respective sides of the split, possibly ceasing
 * to exist on one side of the split. When the split is healed, the connecting
 * servers announce to each other who they think is in each channel and the
 * mode of that channel. If the channel exists on both sides, the JOINs and
 * MODEs are interpreted in an inclusive manner so that both sides of the new
 * connection will agree about which clients are in the channel and what modes
 * the channel has.
*/
class RFC1459Channel {
private:
	static const string _ALLOWED_FLAGS = "opsitnmbv";
	static const string _ALLOWED_TYPES = "&#";
	
	string _name;
	char _type;
	unsigned int _limit;
	string _key;
	string _flags;
	vector<RFC1459User*> _users;

	bool _isLegal(char flag);
public:
	/*
	 * Constructor.
	 * Throws a string if (one of) the flag(s) or the type
	 * are invalid.
	 */
	RFC1459Channel(char type, string name, string flags);
	
	/*
	 * Destructor.
	 * Clears the list of users in the channel,
	 * effectively calling their constructors.
	 */
	virtual ~RFC1459Channel();

	/*
	 * Returns the name of the channel
	 */
	string getName();

	/*
	 * Returns the type of the channel.
	 * This implementation supports two types of channel: 
	 * distributed (#) and local (&). More documentation about this
	 * can be found in RFC 1459, chapter 1.3
	 */
	char getType();

	/*
	 * Returns the user limit for this channel.
	 */
	unsigned int getLimit();

	/*
	 * Returns if the supplied key matched with the
	 * channel-key
	 */
	bool compareKey(string key);

	/*
	 * Returns whether the channel has the supplied flag.
	 */
	bool hasFlag(char flag);

	/*
	  Returns the flags for this channel.
	 */
	string getFlags();
	
	/*
	 * Sets or removes the flag for the channel.
	 * Throws a string if the flag is invalid.
	 */
	void setFlag(char flag, bool enabled);
	
	/*
	 * Adds a user to the channel.
	 */
	void addUser(RFC1459User* user);
	
	/*
	 * Removes a user from the channel.
	 */
	void removeUser(RFC1459User* user);
	
	/* 
	 * Convenience method to remove a user.
	 */
	void removeUser(string nick);
	
	/*
	 * Returns the user that has the corresponding nick.
	 */
	RFC1459User* getUser(string nick);
	
	/*
	 * Returns the users currently in the channel.
	 */
	vector<RFC1459User*> getUsers();
};

#endif /* RFC1459CHANNEL_H */
