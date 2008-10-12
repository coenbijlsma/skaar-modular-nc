#include "RFC1459Channel.h"

const string RFC1459Channel::_ALLOWED_FLAGS = "opsitnmbv";
const string RFC1459Channel::_ALLOWED_TYPES = "&#";

RFC1459Channel::RFC1459Channel(char type, string name, unsigned int limit, string key, string flags){
	for(unsigned int i = 0; i < flags.length(); i++){
		if( ! _isLegal(flags[i]) ){
			throw string("Invalid flag");
		}
	}
	
	if(RFC1459Channel::_ALLOWED_TYPES.find(type, 0) == string::npos){
		throw string("Invalid channel type");
	}
	
	_type = type;
	_name = name;
	_flags = flags;
	_limit = limit;
	_key = key;
}

RFC1459Channel::~RFC1459Channel(){
	_users.clear();
}

bool RFC1459Channel::_isLegal(char flag){
	return !(_ALLOWED_FLAGS.find(flag, 0) == string::npos);
}

string RFC1459Channel::getName(){
	return _name;
}

char RFC1459Channel::getType(){
	return _type;
}

unsigned int RFC1459Channel::getLimit(){
	return _limit;
}

bool RFC1459Channel::compareKey(string key){
	return _key == key;
}

bool RFC1459Channel::hasFlag(char flag){
	return !(_flags.find(flag, 0) == string::npos);
}

string RFC1459Channel::getFlags(){
	return _flags;
}

void RFC1459Channel::setFlag(char flag, bool enabled){
	if( ! _isLegal(flag) ){
		throw string("Invalid flag");
	}
	
	if( hasFlag(flag) &&  enabled){
		return;
	}
	if( !hasFlag(flag) && !enabled){
		return;
	}
	if( !hasFlag(flag) && enabled){
		_flags.append(flag, 0);
	}
	if( hasFlag(flag) && !enabled){
		_flags.erase(_flags.find(flag, 0), 1);
	}
}

void RFC1459Channel::addUser(RFC1459User* user){
	for(unsigned int i = 0; i < _users.size(); i++){
		if(_users.at(i) == user){
			return;
		}
	}
	
	_users.push_back(user);
}

void RFC1459Channel::removeUser(RFC1459User* user){
	removeUser(user->getNick());
}

void RFC1459Channel::removeUser(string nick){
	for(vector<RFC1459User*>::iterator it = _users.begin(); it != _users.end(); it++){
		if( (*it)->getNick() == nick){
			_users.erase(it);
			return;
		}
	}
}

RFC1459User* RFC1459Channel::getUser(string nick){
	for(vector<RFC1459User*>::iterator it = _users.begin(); it != _users.end(); it++){
		if( (*it)->getNick() == nick){
			return (*it);
		}
	}
	return (RFC1459User*)0;
}

vector<RFC1459User*> RFC1459Channel::getUsers(){
	return _users;
}
