#include "TerminalGUI.h"
#include <iostream>

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
