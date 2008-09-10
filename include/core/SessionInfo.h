/**
 * @file SessionInfo.h
 * @brief Information about the current session.
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

#ifndef SESSIONINFO_H
#define SESSIONINFO_H

#include <vector>
#include "SkaarUser.h"
#include "AbstractGUI.h"

using namespace std;

class SessionInfo {
private:
	SkaarUser* _user;
	vector<AbstractGUI*> _windowlist;
		
public:
	
	/*
	 * Constructor.
	 * Sets the user after it checks whether
	 * the user == 0, and throws a string if so.
	 */
	SessionInfo(SkaarUser* user);
	
	/*
	 * Destructor. Does nothing at this time.
	 */
	virtual ~SessionInfo();
	
	/*
	 * Returns the SkaarUser that started
	 * this session.
	 */
	SkaarUser* getUser();
	
	/*
	 * Returns the currently active window.
	 * If none, returns (AbstractGUI*)0.
	 */
	AbstractGUI* getActiveWindow();
	
	/*
	 * Returns the AbstractGUI* at position pos.
	 * If that position doesn't exist, a 0 pointer
	 * is returned.
	 */
	AbstractGUI* getWindowAt(int pos);
	
	/*
	 * Returns the AbstractGUI* that was created to
	 * communicate with the requested receiver.
	 * Also, if that window doesn't exist,
	 * (AbstractGUI*)0 is returned.
	 */
	AbstractGUI* getWindowFor(string receiver);
	
	/*
	 * Returns all the currently available windows.
	 */
	vector<AbstractGUI*> getWindowList();

	/*
	 * Adds the window to the list if available windows.
	 * Returns true on success, and false if the window 
	 * already exists in the list.
	 */
	bool addWindow(AbstractGUI* window);
	
};

#endif
