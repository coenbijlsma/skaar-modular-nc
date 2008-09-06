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
	SessionInfo(SkaarUser* user);
	virtual ~SessionInfo();
	
	SkaarUser* getUser();
	AbstractGUI* getActiveWindow();
	AbstractGUI* getWindowAt(int pos);
	vector<AbstractGUI*> getWindowList();

	bool addWindow(AbstractGUI* window);
	
};

#endif
