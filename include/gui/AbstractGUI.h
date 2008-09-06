#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <string>

using namespace std;

class AbstractGUI {

public:
	
	virtual ~AbstractGUI() {}
	virtual void addContent(string content) =0;
	virtual bool redraw() =0;
	virtual bool scrollContent(int amount) =0;
	virtual void setActive(bool active) =0;
	virtual bool isActive() =0;
	virtual void setReceiver(string recv) =0;
	virtual string getReceiver() =0;
	virtual string getServer() =0;
	virtual void setServer(string server) =0;
	
};

#endif
