/**
 * @file AbstractGUI.h
 * @brief Abstraction for User Interfaces of Skaar.
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

#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <string>

using namespace std;

class AbstractGUI {

public:
	
	/*
	 * Destructor.
	 */	
	 virtual ~AbstractGUI() {};
	
	/*
	 * Adds the provided content string to the
	 * screen. How this is done depends on the
	 * implementation of AbstractGUI that is used.
	 * see the header file of that implementation
	 * for more details.
	 */
	virtual void addContent(string content) =0;
	
	/*
	 * Redraws this window. Refer to the headerfile
	 * of the desired implementation for more
	 * information about how it's done.
	 * This also may or may not work in the implementation.
	 */
	virtual bool redraw() =0;
	
	/*
	 * Scrolls the content amount lines.
	 * This method may or may not do anything,
	 * dependent on the implementation.
	 */
	virtual bool scrollContent(int amount) =0;
	
	/*
	 * Sets this screen as the active one.
	 * On some implementations, this method
	 * does nothing.
	 */
	virtual void setActive(bool active) =0;
	
	/*
	 * Returns whether this is the active 
	 * window. Note that, if this method
	 * does nothing in an implementation,
	 * it should return true (because I use
	 * it to determine the active screen from
	 * an array of AbstractGUI's).
	 */
	virtual bool isActive() =0;
	
	/*
	 * Sets who is on the other end of the line.
	 * Is also used to keep different windows apart.
	 */
	virtual void setReceiver(string recv) =0;
	
	/*
	 * Returns who receives the message if the
	 * user types one in the screen.
	 */
	virtual string getReceiver() =0;
	
	/*
	 * Returns the server (or it's ip-address) messages
	 * from this window will be sent to.
	 */
	virtual string getServer() =0;
	
	/*
	 * Sets the server messages from this window 
	 * will be sent to.
	 */
	virtual void setServer(string server) =0;
	
	/*
	 * Creates a new AbstractGUI, so the
	 * classes and/or functions that use this
	 * class don't have to know how to do that.
	 */
	virtual AbstractGUI* create() =0;
	
};

#endif
