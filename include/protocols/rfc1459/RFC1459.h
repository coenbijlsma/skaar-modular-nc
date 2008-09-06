#ifndef RFC1459_H
#define RFC1459_H

#include <string>
#include <vector>
#include "AbstractProtocol.h"
#include "AbstractMessage.h"

using namespace std;

class RFC1459 : public AbstractProtocol {
private:
	vector<string> _registeredMessages;
	
public:
	RFC1459();
	virtual ~RFC1459();
	
	vector<string> registeredMessages();
	bool registerMessage(string message);
	bool unregisterMessage(string message);
	bool isRegistered(string message);
	AbstractMessage* translateIncoming(string raw);
	string toProtocolString(string raw);
	
};

#endif
