#include "SkaarConfigSection.h"
#include <iostream>

SkaarConfigSection::SkaarConfigSection(string name){
	_name = name;
}

SkaarConfigSection::~SkaarConfigSection(){
	_entries.clear();
}

string SkaarConfigSection::name(){
	return _name;
}

string SkaarConfigSection::get(string setting){
	map<string, string>::iterator it = _entries.find(setting);
	
	if(it == _entries.end()){
		return "";
	}
	return _entries[setting];
}

void SkaarConfigSection::set(string setting, string value){
	_entries[setting] = value;
}

map<string, string> SkaarConfigSection::all(){
	return _entries;
}
