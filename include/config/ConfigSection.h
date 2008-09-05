#ifndef CONFIGSECTION_H
#define CONFIGSECTION_H

#include <string>
#include <map>

using namespace std;

class ConfigSection {
private:
	string _name;
	map<string, string> _entries;

public:
	ConfigSection(string name);
	virtual ~ConfigSection();
	
	string name();
	string get(string setting);
	void set(string setting, string value);
	map<string, string> all();
};

#endif /* CONFIGSECTION_H */
