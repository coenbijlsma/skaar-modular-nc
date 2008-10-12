#include "Screen.h"
#include <stdio.h>

void Screen::_init(){
	if(_panel == NULL){
		throw string("The PANEL for this Screen cannot be NULL");
	}
	
	_screenBuffer = new ScreenBuffer(); // Even useful??
	
	// Enable scrolling
	scrollok(panel_window(_panel), true);
	_log = 0;
}

Screen::Screen(string server, int lines, int cols, int y, int x ){
	if(lines > (LINES -2)){
		lines = LINES -2;
	}
	if(cols > COLS){
		cols = cols;
	}
	_panel = new_panel( newwin(lines, cols, y, x) );
	_server = server;
	
	_init();
}

Screen::Screen(string server, PANEL* panel){
	_panel = panel;
	WINDOW* win = newwin( (LINES -2), COLS, 0, 0);
	WINDOW* old_win = panel_window(panel);
	replace_panel(_panel, win);
	delwin(old_win);
	
	_server = server;
	
	_init();
}

Screen::Screen(){
	_panel = new_panel( newwin(LINES -2, COLS, 0, 0) );
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

void Screen::setLog(SkaarLog* log){
	_log = log;
}

void Screen::addContent(string content){
	// for some reason ncurses handles strings containins \r not so well,
	// so strip it out here
	if(content.size() != 0){
		for(string::size_type spos = content.find('\r', 0); spos != string::npos; spos = content.find('\r', 0)){
			content.erase(spos, 1);
		}
	}	
	
	WINDOW* win = panel_window(_panel);
	
	_screenBuffer->put(content);
	
	if(_log != 0){
		if(win == 0){
			_log->append("WINDOW* is null!");
		}
		if(content.size() == 0){
			_log->append("Not appending empty string.");
		}
		_log->save();
	}
	
	if(content.size() > 0){
		waddstr(win, content.c_str());
		wrefresh(win);
	}
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
		_active = true;
	}else{
		if(hide_panel(_panel) == ERR){
			throw string("Could not hide the Screen.");
		}
		_active = false;
	}
	
	update_panels();
	doupdate();
}

bool Screen::isActive(){
	return _active;
}

void Screen::setReceiver(string recv){
	_receiver = recv;
}

string Screen::getReceiver(){
	return _receiver;
}

string Screen::getServer(){
	return _server;
}

void Screen::setServer(string server){
	_server = server;
}

AbstractGUI* Screen::create(){
	return new Screen();
}
