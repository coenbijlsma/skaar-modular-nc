#include "RFC1459.h"
#include "StringTokenizer.h"
#include <cctype> // std::toupper
#include <stdlib.h>

/* The messages from RFC1459 */
#include "AdminMessage.h"
#include "PassMessage.h"
#include "UserMessage.h"
#include "NickMessage.h"
#include "JoinMessage.h"
#include "PrivmsgMessage.h"

RFC1459::RFC1459(){}

RFC1459::~RFC1459(){}

vector<string> RFC1459::registeredMessages(){
	return _registeredMessages;
}

bool RFC1459::registerMessage(string message){
	if(isRegisteredMessage(message)){
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

bool RFC1459::isRegisteredMessage(string message){
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
		if( ! isRegisteredMessage(AdminMessage::COMMAND)){
			registerMessage(AdminMessage::COMMAND);
		}
		return (AbstractMessage*)m;
	}
	if(command == JoinMessage::COMMAND){
		JoinMessage* m = new JoinMessage(this, raw);
		
		if( ! isRegisteredMessage(JoinMessage::COMMAND)){
			registerMessage(JoinMessage::COMMAND);
		}
		return (AbstractMessage*)m;
	}
	/* XXX */
}

string RFC1459::toProtocolString(SessionInfo* sessionInfo, string raw){
	/* If raw starts with a slash, it contains the command. If not, it's a PRIVMSG */
	if(raw[0] == '/'){
	}else{
		/* We have a PRIVMSG */
		string receiver = sessionInfo->getActiveWindow()->getReceiver();
		string final_raw("PRIVMSG ");
		final_raw.append(receiver);
		final_raw.append(" ");
		final_raw.append(raw);
		final_raw.append(1, '\r');
		final_raw.append(1, '\n');
		return final_raw;
	}
	return string("");
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
	for(vector<RFC1459Channel*>::iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); it++){
		if( (*it)->getName() == name){
			RFC1459Channel* chan = (*it);
			_joinedChannels.erase(it);
			delete chan;
		}
	}
}

vector<string> RFC1459::getRegisterSequence(SessionInfo* sessionInfo){
	vector<string> reg;
	
	string passwd = sessionInfo->getConfig()->getValue("core", "password");
	string nick = sessionInfo->getConfig()->getValue("core", "nick");
	char* user = getenv("USER");
	string realname = sessionInfo->getConfig()->getValue("core", "realname");
	
	if(passwd.size() == 0){
		throw string("No password defined.");
	}
	if(nick.size() == 0){
		throw string("No nick specified");
	}
	if(realname.size() == 0 && user == 0){
		throw string("No user information found");
	}
	if(realname.size() == 0 && user != 0){
		realname = string(user);
	}
	if(user == 0 && realname.size() > 0){
		user = const_cast<char*>(realname.c_str());
	}
		
	string pass_msg = "PASS ";
	
	pass_msg.append(passwd);
	pass_msg.append(this->getMessageSeparator());
	reg.push_back(pass_msg);
	
	string nick_msg = "NICK ";
	nick_msg.append(nick);
	nick_msg.append(this->getMessageSeparator());
	reg.push_back(nick_msg);
	
	string user_msg = "USER ";
	user_msg.append(user);
	user_msg.append(" foo bar ");
	user_msg.append(realname);
	user_msg.append(this->getMessageSeparator());
	reg.push_back(user_msg);
	
	return reg;
}

string RFC1459::getMessageSeparator(){
	string s("\r\n");
	return s;
}
