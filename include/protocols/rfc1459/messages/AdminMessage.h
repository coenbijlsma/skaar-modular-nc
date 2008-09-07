#ifndef ADMINMESSAGE_H
#define ADMINMESSAGE_H

#include <string>
#include <vector>
#include "SkaarUser.h"
#include "RFC1459.h"

using namespace std;

class AdminMessage : public AbstractMessage {
private:
	RFC1459* _protocol;
	string _raw;
	string _prefix;
	vector<string> _params;
	SkaarUser* _user;
	
	void _init();

public:
	static const string COMMAND = "ADMIN";
	static const unsigned int MINPARAMS = 0;
	
	AdminMessage(RFC1459* protocol, string raw);
	~AdminMessage();
	
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

#endif
