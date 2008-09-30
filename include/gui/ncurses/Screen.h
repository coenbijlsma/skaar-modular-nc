/**
 * @file Screen.h
 * @brief ncurses implementation of AbstractGUI
 *
 * Copyright (c) 2008 Coen Bijlsma
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <panel.h>
#include <ncurses.h>
#include <string>
#include "AbstractGUI.h"
#include "ScreenBuffer.h"

using namespace std;

class Screen : public AbstractGUI {
private:
	PANEL* _panel;
	ScreenBuffer* _screenBuffer;
	string _receiver;
	string _server;
			
	/*
	 * Some initial functions to be called by the 
	 * constructor.
	 */
	void _init();		
public:

	/*
	 * Initializes the Screen in a new PANEL. If you use the 
	 * default constructor, a full-screen Screen is created.
	 */
	Screen(string server, int lines = 0, int cols = 0, int y = 0, int x = 0);
	
	/*
	 * Initializes the Screen with the given PANEL
	 */
	Screen(string server, PANEL* panel);
	
	/*
	 * Standard constructor for compatibility with the
	 * abstraction AbstractGUI
	 */
	Screen();
	
	/*
	 * Flushes the ScreenBuffer, and then deletes the 
	 * PANEL and the WINDOW that sits therein.
	 */
	virtual ~Screen();
	
	/*
	 * Returns the PANEL that this Screen writes to.
	 * You can use this if you want to perform some
	 * lowlevel functions.
	 */
	PANEL* getPANEL();
	
	/*
	 * Adds content to the ScreenBuffer and refreshes the
	 * WINDOW, so that the content is shown at the physical 
	 * screen.
	 */
	void addContent(string content);
	
	/*
	 * Tries to redraw the WINDOW and returns whether 
	 * it succeeded or not.
	 */
	bool redraw();
	
	/*
	 * Scrolls the content in the Screen up or down the
	 * amount of lines entered. A positive amount scrolls
	 * down, a negative amount scrolls up (as in back up).
	 * @see man 3 scroll
	 */
	bool scrollContent(int amount);
	
	/*
	 * Sets or unsets this Screen as the currently active Screen
	 * for Skaar. The active Screen is visible to the user,
	 * non-active Screens aren't.
	 */
	void setActive(bool active);
	
	/*
	 * Returns whether or not this Screen is currently
	 * the active one.
	 */
	bool isActive();
	
	/*
	 * Sets who (or what) should receive the messages 
	 * typed in this Screen.
	 */
	void setReceiver(string recv);
	
	/*
	 * Returns who (or what) receives the messages
	 * typed in this Screen.
	 */
	string getReceiver();
	
	/*
	 * Returns the server that is used when sending
	 * data.
	 */
	string getServer();
	
	/**/
	void setServer(string server);

	AbstractGUI* create();	
};

#endif
