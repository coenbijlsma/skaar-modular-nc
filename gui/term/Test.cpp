#include "TerminalGUI.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
	TerminalGUI* tg = new TerminalGUI();
	
	tg->addContent("I am a TerminalGUI");	
	delete tg;
	cout << "Testing done" << endl;
	return 0;
}
