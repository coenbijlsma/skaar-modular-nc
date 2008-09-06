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
	User(string username, string nick, string password);
	~User();
	
	string getUsername();
	string getNick();
	string getPassword();
	
	void setUsername(string un);
	void setNick(string n);
	void setPassword(string pwd);
	
};

#endif
