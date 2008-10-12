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
#include "SkaarConfig.h"
#include "AbstractGUI.h"
#include "AbstractInputReader.h"

using namespace std;

class SessionInfo {
private:
	SkaarUser* _user;
	SkaarConfig* _config;
	vector<AbstractGUI*> _windowlist;
	AbstractInputReader* _inputReader;
	
public:
	
	/*
	 * Constructor.
	 * Sets the user after it checks whether
	 * the user == 0, and throws a string if so.
	 */
	SessionInfo(SkaarUser* user, SkaarConfig* config);
	
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
	 * Returns the configuration for
	 * the current instance of Skaar.
	 */
	SkaarConfig* getConfig();
	
	/*
	 * Returns the currently active window.
	 * If none, returns (AbstractGUI*)0.
	 */
	AbstractGUI* getActiveWindow();
	
	/*
	 * Returns the AbstractGUI* at position pos.
	 * If pos is equal to the position after the
	 * last one, a new window is returned.
	 * Apart from the above exception, if the
	 * position is not in the list of windows,
	 * an (AbstractGUI*)0 is returned.
	 */
	AbstractGUI* getWindowAt(unsigned int pos);
	
	/*
	 * Returns the AbstractGUI* that was created to
	 * communicate with the requested receiver.
	 * Also, if that window doesn't exist,
	 * (AbstractGUI*)0 is returned.
	 */
	AbstractGUI* getWindowFor(string receiver);
	
	/*
	 * Returns the amount of windows currently
	 * in the list.
	 */
	int getWindowCount();
	
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
	
	/*
	 * GET INPUTREADER
	 */
	AbstractInputReader* getInputReader();
	
	/*
	 * SET INPUTREADER
	 */
	void setInputReader(AbstractInputReader* reader);
	
};

#endif
