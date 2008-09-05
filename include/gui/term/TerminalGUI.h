#ifndef TERMINALGUI_H
#define TERMINALGUI_H

#include <string>
#include "AbstractGUI.h"

using namespace std;

class TerminalGUI : public AbstractGUI {

public:
	TerminalGUI();
	~TerminalGUI();
	
	void addContent(string content);
	bool redraw();
	bool scrollContent(int amount);
	void setActive(bool active);
	bool isActive();
};

#endif
