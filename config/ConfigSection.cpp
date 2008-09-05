#include "ConfigSection.h"
#include <iostream>

ConfigSection::ConfigSection(string name){
	_name = name;
}

ConfigSection::~ConfigSection(){}

string ConfigSection::name(){
	return _name;
}

string ConfigSection::get(string setting){
	map<string, string>::iterator it = _entries.find(setting);
	
	if(it == _entries.end()){
		return "";
	}
	return _entries[setting];
}

void ConfigSection::set(string setting, string value){
	_entries[setting] = value;
}

map<string, string> ConfigSection::all(){
	return _entries;
}
