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
	Screen(int lines = 0, int cols = 0, int y = 0, int x = 0);
	
	/*
	 * Initializes the Screen with the given PANEL
	 */
	Screen(PANEL* panel);
	
	/*
	 * Flushes the ScreenBuffer, and then deletes the 
	 * PANEL and the WINDOW that sits therein.
	 */
	~Screen();
	
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
	
};

#endif
