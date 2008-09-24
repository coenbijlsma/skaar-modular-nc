/**
 * @file UserMessage.h
 * @brief Implementation for the USER message of RFC1459
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

#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <string>
#include <vector>
#include "SkaarUser.h"
#include "RFC1459.h"

using namespace std;

/**
 * Command: 	USER
 * Parameters: 	<username> <hostname> <servername> <realname>
 * 
 * The USER message is used at the beginning of connection to specify the
 * username,hostname, servername and realname of s new user. It is also used in
 * communication between servers to indicate new user arriving on IRC, since
 * only after both USER and NICK have been received from a client does a user
 * become registered.
 * 
 * Between servers USER must to be prefixed with client's NICKname. Note that
 * hostname and servername are normally ignored by the IRC server when the USER
 * command comes from a directly connected client (for security reasons), but
 * they are used in server to server communication. This means that a NICK must
 * always be sent to a remote server when a new user is being introduced to the
 * rest of the network before the accompanying USER is sent.
 * 
 * It must be noted that realname parameter must be the last parameter, because
 * it may contain space characters and must be prefixed with a colon (':') to
 * make sure this is recognised as such.
 * 
 * Since it is easy for a client to lie about its username by relying solely on 
 * the USER message, the use of an "Identity Server" is recommended. If the host
 * which a user connects from has such a server enabled the username is set to
 * that as in the reply from the "Identity Server".
 * 
 * Numeric Replies:
 * ERR_NEEDMOREPARAMS 	ERR_ALREADYREGISTRED
 * 
 * Examples:
 * 
 * USER guest tolmoon tolsun :Ronnie Reagan
 *                       ; User registering themselves with a
 *                       username of "guest" and real name
 *                       "Ronnie Reagan".
 * 
 * :testnick USER guest tolmoon tolsun :Ronnie Reagan
 *                       ; message between servers with the
 *                       nickname for which the USER command
 *                       belongs to
 */
class UserMessage : public AbstractMessage {
private:
	RFC1459* _protocol;
	string _raw;
	string _prefix;
	vector<string> _params;
	
	void _init();

public:
	static const string COMMAND = "USER";
	static const unsigned int MINPARAMS = 4;
	
	UserMessage(RFC1459* protocol, string raw);
	~UserMessage();
	
	string getPrefix();
	string getSenderNick();
	string getReceiver();
	string getCommand();
	unsigned int getMinParams();
	
	/**/
	string format(string format);
	vector<string> getParams();
	
	RFC1459* getProtocol();
};

#endif /* USERMESSAGE_H */
