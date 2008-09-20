#include "RFC1459.h"
#include "StringTokenizer.h"
#include <cctype> // std::toupper

/* The messages from RFC1459 */
#include "AdminMessage.h"

RFC1459::RFC1459(){}

RFC1459::~RFC1459(){}

vector<string> RFC1459::registeredMessages(){
	return _registeredMessages();
}

bool RFC1459::registerMessage(string message){
	if(isRegistered(message)){
		return false;
	}
		
	_registeredMessages.push_back(message);
	return true;
}

bool RFC1459::unregisterMessage(string message){
	for(vector<string>::iterator it = _registeredMessages.begin(); it != _registeredMessages.end(); it++){
		if( (*it) == message){
			_registeredMessages.erase(it);
			return true;
		}
	}
	return false;
}

bool RFC1459::isRegistered(string message){
	for(int i = 0; i < _registeredMessages.size(); i++){
		if(_registeredMessages.at(i) == message){
			return true;
		}
	}
	
	return false;
}

AbstractMessage* RFC1459::translateIncoming(string raw){
	StringTokenizer	st(string(raw), ' ');
	string command = st.next();
	
	/* Do we have a prefix? */
	if(command[0] == ':'){
		command = st.next();
	}
	
	/* Make sure the command is in uppercase */
	for(int i = 0; i < command.length(); i++){
		command[i] = toupper(command[i]);
	}
		
	/* And then return the correct message */
	if(command == AdminMessage::COMMAND){
		AdminMessage* m = new AdminMessage(this, raw);
		
		/* Register the message if needed */
		if( ! isRegistered(AdminMessage::COMMAND)){
			registerMessage(AdminMessage::COMMAND);
		}
		return m;
	}
	/* XXX */
}

string RFC1459::toProtocolString(SessionInfo* sessionInfo, string raw){
	/* If raw starts with a slash, it contains the command. If not, it's a PRIVMSG */
	if(raw[0] == '/'){
	}else{
	}
	return string;
}

void RFC1459::addJoinedChannel(RFC1459Channel* chan){
	for(int i = 0; i < _joinedChannels.size(); i++){
		if(_joinedChannels.at(i)->getName() == chan->getName()){
			return;
		}
	}

	_joinedChannels.push_back(chan);
}

void RFC1459::removeJoinedChannel(RFC1459Channel* chan){
	removeJoinedChannel(chan->getName());
}

void RFC1459::removeJoinedChannel(string name){
	for(vector<RFC1459Channel*>::iterator it = _joinedChannels.begin(); it != _joinedChanneld.end(); it++){
		if( (it*)->getName() == name){
			RFC1459Channel* chan = (it*);
			_joinedChannels.erase(it);
			delete chan;
		}
	}
}
