/**
 * @file SkaarUser.h
 * @brief Represents the current user.
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

#ifndef SKAARUSER_H
#define SKAARUSER_H

#include <string>

using namespace std;

class SkaarUser {
private:
	string _username;
	string _nick;
	string _password;

public:

	/*
	 * Constructor.
	 */
	SkaarUser(string username, string nick, string password);
	
	/*
	 * Destructor. Does nothing at the time.
	 */
	virtual ~SkaarUser();
	
	/*
	 * Returns the username.
	 */
	string getUsername();
	
	/*
	 * Returns the nickname of the user.
	 */
	string getNick();
	
	/*
	 * Returns the password for this user.
	 */
	string getPassword();
	
	/*
	 * Sets the username to un.
	 * Note that this changes nothing to the
	 * username used in the protocol that is communicated
	 * over the socket eventually.
	 */
	void setUsername(string un);
	
	/*
	 * Sets the nickname of the user to n.
	 * Also note that this does not change the nickname
	 * for the protocol. In fact, this method should be called
	 * only after a successful nickchange, but I give you the 
	 * freedom to do otherwise.
	 */
	void setNick(string n);
	
	/*
	 * Sets the password for the user.
	 * Again, this does not change the password
	 * for the connection. As you may have noticed
	 * by now, this is a pure data class. There, I've said it.
	 */
	void setPassword(string pwd);
	
};

#endif
