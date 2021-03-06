#include "Screen.h"
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

int main(int argc, char** argv){
	vector<Screen*> screens;
	initscr();
	cbreak();
	noecho();
	
	string server = "localhost";
		
	AbstractGUI* scr = new Screen(server);
	Screen* scr1 = new Screen(server);
	Screen* scr2 = new Screen(server);
	
	scr->addContent("I am Screen 1");
	scr->addContent("Dusch...");
	scr1->addContent("And I am Screen 2");
	scr2->addContent("And I am Screen 3");

	scr->setActive(true);
	getch();

	scr->setActive(false);
	scr1->setActive(true);
	getch();

	scr1->setActive(false);
	scr2->setActive(true);	
	getch();
	
	delete scr;
	delete scr1;
	delete scr2;
	endwin();
	
	cout << "Testing done" << endl;
	return 0;
}
