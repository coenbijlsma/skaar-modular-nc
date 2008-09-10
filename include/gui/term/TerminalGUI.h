/**
 * @file TerminalGUI.h
 * @brief The standard UI Skaar uses as fallback if ncurses doesn't work.
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
#ifndef TERMINALGUI_H
#define TERMINALGUI_H

#include <string>
#include "AbstractGUI.h"

using namespace std;

/*
 * NI means Not Implemented as in that the function exists only
 * for compatibility with AbstractGUI bus does nothing at all.
 */
class TerminalGUI : public AbstractGUI {
private:
	string _server;
	string _receiver;
public:

	/*
	 * Constructor.
	 */
	TerminalGUI(string server);
	~TerminalGUI();
	
	/*
	 * Puts the content on the screen.
	 * In this implementation the screen
	 * is just stdout.
	 */
	void addContent(string content);
	
	/*
	 * Does nothing in this implementation
	 * but it returns true.
	 */
	bool redraw(); // NI
	
	/*
	 * Does nothing in this implementation
	 * but it returns true.
	 */
	bool scrollContent(int amount); // NI
	
	/*
	 * Does nothing in this implementation
	 * but it returns true;
	 */
	void setActive(bool active); // NI
	
	/*
	 * Returns true, because the TerminalGUI
	 * only implements one screen, so it is 
	 * always the active one.
	 */
	bool isActive(); // NI
	
	/*
	 * Sets the receiver of this message.
	 * Not that this is very useful in this
	 * implementation, because there is only
	 * one screen.
	 */
	void setReceiver(string recv);
	
	/*
	 * Returns who receives messages that come
	 * from this screen (but because there is only
	 * one screen in this case, that doesn't have to
	 * be accurate).
	 */
	string getReceiver(); 
	
	/*
	 * Sets the server the messages are sent to.
	 */
	string getServer();
	
	/*
	 * Returns the server messages from this 
	 * screen are sent to.
	 */
	void setServer(string server);
};

#endif
