#include "SessionInfo.h"

SessionInfo::SessionInfo(SkaarUser* user, SkaarConfig* config){
	if(user == 0){
		throw string("The user for the SessionInfo may not be NULL");
	}
	if(config == 0){
		throw string("I simply refuse to handle empty configurations.");
	}
	_user = user;
	_config = config;
}

SessionInfo::~SessionInfo(){
	delete _user;
	delete _config;
	delete _inputReader;
	
	while( ! _windowlist.empty() ){
		AbstractGUI* gui = *(_windowlist.begin());
		_windowlist.erase(_windowlist.begin());
		delete gui;
	}
}

SkaarUser* SessionInfo::getUser(){
	return _user;
}

SkaarConfig* SessionInfo::getConfig(){
	return _config;
}

AbstractGUI* SessionInfo::getActiveWindow(){
	for(unsigned int i = 0; i < _windowlist.size(); i++){
		AbstractGUI* ag = _windowlist.at(i);
		if(ag->isActive()){
			return ag;
		}
	}
	return (AbstractGUI*)0;
}

AbstractGUI* SessionInfo::getWindowAt(unsigned int pos){
	if(pos >= 0 && pos < _windowlist.size()){
		return _windowlist.at(pos);
	}else if(pos == _windowlist.size()){
		/* If the pos == _windowlist.size(), create a new one */
		AbstractGUI* last = _windowlist.at(_windowlist.size() -1);
		AbstractGUI* retval = last->create();
		//retval->setInputReader(last->getInputReader()); // Use the same InputReader
		addWindow(retval);
		return retval;
	}
	return (AbstractGUI*)0;
}

AbstractGUI* SessionInfo::getWindowFor(string receiver){
	for(unsigned int i = 0; i < _windowlist.size(); i++){
		AbstractGUI* gui = _windowlist.at(i);
		if( gui->getReceiver() == receiver){
			return gui;
		}
	}
	return (AbstractGUI*)0;
}

int SessionInfo::getWindowCount(){
	return _windowlist.size();
}

vector<AbstractGUI*> SessionInfo::getWindowList(){
	return _windowlist;
}

bool SessionInfo::addWindow(AbstractGUI* window){
	for(unsigned int i = 0; i < _windowlist.size(); i++){
		if(_windowlist.at(i) == window){
			return false;
		}
	}
	_windowlist.push_back(window);
	return true;
}

AbstractInputReader* SessionInfo::getInputReader(){
	return _inputReader;
}

void SessionInfo::setInputReader(AbstractInputReader* reader){
	_inputReader = reader;
}
