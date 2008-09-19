#include "RFC1459User.h"

RFC1459User::RFC1459User(string name, string realName, int flags){
	if(flags > (OPERATOR + WALLOPS + SERVER_NOTICES + INVISIBLE) || flags < NO_FLAGS){
		throw string("Invalid flag value for user.");
	}
	
	_name = name;
	_realName = realName;
	_flags = flags;
}

RFC1459User::~RFC1459User(){}

string RFC1459User::getName(){
	return _name;
}

string RFC1459User::getRealName(){
	return _realName;
}

int RFC1459User::getFlags(){
	return _flags;
}

void RFC1459User::setFlag(int flag, bool enabled){
	if(flag > OPERATOR || flag < NO_FLAGS || ( flag != INVISIBLE && (flag % 2) > 0) ){
		throw string("Invalid flag");
	}
	
	if(_flags == NO_FLAGS){
		if(enabled){
			_flags += flag;
			return;
		}else{
			throw string("Flag not set");
		}
	}
	
	if(_flags < flag){
		if(enabled){
			_flags += flag;
		}else{
			throw string("Flag not set");
		}
		return;
	}else{
		if(_flags >= flag && _flags <= (flag + flag - 1) ){
			if(enabled){
				throw string("Flag already set");
			}else{
				_flags -= flag;
			}
		}else{
			if(enabled){
				_flags += flag;
			}else{
				throw string("Flag not set");
			}
		}
	}	
}

bool RFC1459User::hasFlag(int flag){
	if(_flags == flag){
		return true;
	}
	
	if(_flags < flag || flag < NO_FLAGS || flag > OPERATOR){
		return false;
	}
	
	if( (_flags - flag) >= flag && (_flags - flag) <= (flag + flag -1) ){
		return true;
	}
	return false;
}

