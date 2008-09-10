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
