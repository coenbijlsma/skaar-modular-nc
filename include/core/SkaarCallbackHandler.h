/**
 * @file SkaarCallbackHandler.h
 * @brief Interface for use in commands and actions.
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

#ifndef SKAARCALLBACKHANDLER_H
#define SKAARCALLBACKHANDLER_H

#include "SkaarSocket.h"
#include "SessionInfo.h"

using namespace std;

class SkaarCallbackHandler {
public:
	virtual ~SkaarCallbackHandler(){}
	
	/*
	 * Returns the current SessionInfo
	 */
	virtual SessionInfo* getSessionInfo() =0;
	
	/*
	 * Tries to send a sequence of messages that together form
	 * registration at the server on the other side.
	 * For example, in the IRC protocol, this implies sending
	 * a PASS, NICK and USER message (in that order).
	 */
	virtual bool registerAtConnection(SkaarSocket* sock) =0;
	
	/*
	 * Cleans up the neccessary stuff and exits Skaar.
	 */
	virtual void exit() =0;
};

#endif /* SKAARCALLBACKHANDLER_H */
