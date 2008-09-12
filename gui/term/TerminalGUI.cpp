#include "TerminalGUI.h"
#include <iostream>

TerminalGUI::TerminalGUI(string server){
	_server = server;
}

TerminalGUI::TerminalGUI(){}

TerminalGUI::~TerminalGUI(){}

void TerminalGUI::addContent(string content){
	cout << content << endl;
}

bool TerminalGUI::redraw(){
	return true;
}

bool TerminalGUI::scrollContent(int amount){
	return true;
}

void TerminalGUI::setActive(bool active){}

bool TerminalGUI::isActive(){
	return true;
}

void TerminalGUI::setReceiver(string recv){
	_receiver = recv;
}

string TerminalGUI::getReceiver(){
	return _receiver;
}

string TerminalGUI::getServer(){
	return _server;
}

void TerminalGUI::setServer(string server){
	_server = server;
}

AbstractGUI* create(){
	return new TerminalGUI();
}

