#include <ncurses.h> // scrollok
#include "NCursesInputReader.h"

NCursesInputReader::NCursesInputReader(){
	_input = new_panel( newwin(2, COLS, LINES -2, 0) );
	scrollok(panel_window(_input), true);
}

NCursesInputReader::~NCursesInputReader(){
	WINDOW* win = panel_window(_input);
	del_panel(_input);
	delwin(win);
}

char NCursesInputReader::read(){
	WINDOW* win = panel_window(_input);
	char c = wgetch(win);
	if(c == '\n'){
		this->nir_scroll(1);
	}
	return c;
}

string NCursesInputReader::readLine(){
	WINDOW* win = panel_window(_input);
	string s;
	char c;
	
	while( (c = wgetch(win)) != _NEWLINE){
		s.append(1, c);
	}
	this->nir_scroll(1);
	return s;
}

string NCursesInputReader::read(string delim){
	WINDOW* win = panel_window(_input);
	string s;
	
	while(true){
		if(s.length() >= delim.length()){
			if(s.substr(s.length() - delim.length()) == delim){
				return s.substr(0, s.length() - delim.length());
			}
		}
		s.append(1, wgetch(win));
	}
	
	return s;
}

int NCursesInputReader::nir_scroll(int n){
	return wscrl(panel_window(_input), n);
}

void NCursesInputReader::setActive(bool active){
	if(active){
		if(show_panel(_input) == ERR){
			throw string("Could not show the input panel");
		}
	}else{
		if(hide_panel(_input) == ERR){
			throw string("Could not hide the input panel");
		}
	}
	
	update_panels();
	doupdate();
}
