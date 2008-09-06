#include "TerminalGUI.h"
#include <iostream>

TerminalGUI::TerminalGUI(SkaarSocket* sock){
	_sock = sock;
}

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

SkaarSocket* TerminalGUI::getSocket(){
	return _sock;
}
