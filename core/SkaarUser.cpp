#include "SkaarUser.h"

SkaarUser::SkaarUser(string username, string nick, string password){
	_username = username;
	_nick = nick;
	_password = password;
}

SkaarUser::~SkaarUser(){}

string SkaarUser::getUsername(){
	return _username;
}

string SkaarUser::getNick(){
	return _nick;
}

string SkaarUser::getPassword(){
	return _password;
}

void SkaarUser::setUsername(string un){
	_username = un;
}

void SkaarUser::setNick(string n){
	_nick = n;
}

void SkaarUser::setPassword(string pwd){
	_password = pwd;
}
