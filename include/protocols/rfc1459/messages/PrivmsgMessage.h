/**
 * @file PrivmsgMessage.h
 * @brief Implementation for the PRIVMSG message of RFC1459
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

#ifndef PRIVMSGMESSAGE_H
#define PRIVMSGMESSAGE_H

#include <string>
#include <vector>
#include "SkaarUser.h"
#include "RFC1459.h"

using namespace std;

/**
 */
class PrivmsgMessage : public AbstractMessage {
private:
	RFC1459* _protocol;
	string _raw;
	string _prefix;
	vector<string> _params;
	
	void _init();

public:
	static const string COMMAND;
	static const unsigned int MINPARAMS = 2;
	
	PrivmsgMessage(RFC1459* protocol, string raw);
	~PrivmsgMessage();
	
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

#endif /* PRIVMSGMESSAGE_H */
