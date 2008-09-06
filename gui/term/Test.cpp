#include "TerminalGUI.h"
#include "SkaarSocket.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
	SkaarSocket* sock = new SkaarSocket("server", 80);
	sock->createConnection();
	
	TerminalGUI* tg = new TerminalGUI(sock);
	
	tg->addContent("I am a TerminalGUI");	
	delete sock;
	delete tg;
	cout << "Testing done" << endl;
	return 0;
}
