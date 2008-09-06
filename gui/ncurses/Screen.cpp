#include "Screen.h"
#include <stdio.h>

void Screen::_init(){
	if(_panel == NULL){
		throw string("The PANEL for this Screen cannot be NULL");
	}
	
	_screenBuffer = new ScreenBuffer(); // Even useful??
	
	// Enable scrolling
	scrollok(panel_window(_panel), true);
}

Screen::Screen(SkaarSocket* sock, int lines, int cols, int y, int x ){
	_panel = new_panel( newwin(lines, cols, y, x) );
	_sock = sock;
	
	_init();
}

Screen::Screen(SkaarSocket* sock, PANEL* panel){
	_panel = panel;
	_sock = sock;
	
	_init();
}

Screen::~Screen(){
	delete _screenBuffer;
	WINDOW* win = panel_window(_panel);
	
	// delete the panel
	del_panel(_panel);
	
	// delete the window
	delwin(win);
}

PANEL* Screen::getPANEL(){
	return _panel;
}

void Screen::addContent(string content){
	WINDOW* win = panel_window(_panel);
	
	_screenBuffer->put(content);
	wprintw(win, content.c_str());
	wrefresh(win);
}

bool Screen::redraw(){
	switch(redrawwin(panel_window(_panel)) ){
		case ERR:
			return false;
		default:
			return true;
	}
}

bool Screen::scrollContent(int amount){
	switch(wscrl(panel_window(_panel), amount)){
		case ERR:
			return false;
		default:
			return true;
	}

}

void Screen::setActive(bool active){
	if(active){
		if(show_panel(_panel) == ERR){
			throw string("Could not show the Screen.");
		}
	}else{
		if(hide_panel(_panel) == ERR){
			throw string("Could not hide the Screen.");
		}
	}
	
	update_panels();
	doupdate();
}

bool Screen::isActive(){
	switch(panel_hidden(_panel)){
		case TRUE:
			return true;
		case FALSE:
			return false;
		case ERR:
			throw string("No panel is associated to this Screen.");
		default:
			return false;
	}
}

void Screen::setReceiver(string recv){
	_receiver = recv;
}

string Screen::getReceiver(){
	return _receiver;
}

SkaarSocket* Screen::getSocket(){
	return _sock;
}
