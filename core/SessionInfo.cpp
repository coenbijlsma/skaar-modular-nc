#include "SessionInfo.h"

SessionInfo::SessionInfo(SkaarUser* user){
	if(user == 0){
		throw string("The user for the SessionInfo may not be NULL");
	}
	_user = user;
}

SessionInfo::~SessionInfo(){}

SkaarUser* SessionInfo::getUser(){
	return _user;
}

AbstractGUI* SessionInfo::getActiveWindow(){
	for(int i = 0; i < _windowlist.size(); i++){
		AbstractGUI* ag = _windowlist.at(i);
		if(ag->isActive()){
			return ag;
		}
	}
	return (AbstractGUI*)0;
}

AbstractGUI* SessionInfo::getWindowAt(int pos){
	if(pos >= 0 && pos < _windowlist.size()){
		return _windowlist.at(pos);
	}
	return (AbstractGUI*)0;
}

vector<AbstractGUI*> SessionInfo::getWindowList(){
	return _windowlist;
}

bool SessionInfo::addWindow(AbstractGUI* window){
	for(int i = 0; i < _windowlist.size(); i++){
		if(_windowlist.at(i) == window){
			return false;
		}
	}
	_windowlist.push_back(window);
	return true;
}
