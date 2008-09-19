#include "RFC1459User.h"

RFC1459User::RFC1459User(string nick, string realName, string flags){
	for(int i = 0; i < flags.size(); i++){
		if( ! _isLegal(flags[i]) ){
			throw string("Invalid flag");
		}
	}
	_nick = nick;
	_realName = realName;
	_flags = flags;
}

RFC1459User::~RFC1459User(){}

bool RFC1459User::_isLegal(char flag){
	return !(_ALLOWED_FLAGS.find(flag, 0) == string::npos):
}

string RFC1459User::getNick(){
	return _nick;
}

string RFC1459User::getRealName(){
	return _realName;
}

string RFC1459User::getFlags(){
	return _flags;
}

void RFC1459User::setFlag(char flag, bool enabled){
	if(hasFlag(flag)){
		throw string("Flag already set");
	}
	
	if( ! _isValid(flag) ){
		throw string("Invalid flag");
	}
	
	_flags.append(flag, 1);
}

bool RFC1459User::hasFlag(char flag){
	return !(_flags.find(flag, 0) == string::npos);
}

