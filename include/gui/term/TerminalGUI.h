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
	TerminalGUI(string server);
	~TerminalGUI();
	
	void addContent(string content);
	bool redraw(); // NI
	bool scrollContent(int amount); // NI
	void setActive(bool active); // NI
	bool isActive(); // NI
	void setReceiver(string recv);
	string getReceiver(); 
	string getServer();
	void setServer(string server);
};

#endif
