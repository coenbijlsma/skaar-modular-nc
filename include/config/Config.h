#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigSection.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Config {
private:
	string _filename;
	map<string, ConfigSection*> _sections;
	
	void _init();
	void _writeSection(ofstream* _fs, string name);
	void _writeDefaultConfig();

public:
	
	Config(string filename = "skaar.conf.default");
	~Config();
	
	ConfigSection* getSection(string name);
	string getValue(string section, string setting);
	void setSetting(string section, string setting, string value);
	bool writeConfig();
	
};

#endif /* CONFIG_H */
