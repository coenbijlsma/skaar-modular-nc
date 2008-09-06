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
	SkaarUser(string username, string nick, string password);
	virtual ~SkaarUser();
	
	string getUsername();
	string getNick();
	string getPassword();
	
	void setUsername(string un);
	void setNick(string n);
	void setPassword(string pwd);
	
};

#endif
