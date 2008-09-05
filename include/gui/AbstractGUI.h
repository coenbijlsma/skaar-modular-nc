#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <string>

using namespace std;

class AbstractGUI {

public:
	virtual void addContent(string content) =0;
	virtual bool redraw() =0;
	virtual bool scrollContent(int amount) =0;
	virtual void setActive(bool active) =0;
	virtual bool isActive() =0;
};

#endif
