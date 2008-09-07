#include "Config.h"
#include "StringTokenizer.h"

Config::Config(string filename){
	_filename = filename;
	
	ifstream _ifstream(_filename.c_str(), ios::in);
	
	if( ! _ifstream.is_open()){
		cerr << "File not found, trying default config." << endl;
		_filename = "skaar.conf.default";
		_ifstream.open(_filename.c_str(), ios::in);
		
		if( ! _ifstream.is_open()){
			cerr << "Default config not found, creating one." << endl;
			_writeDefaultConfig();
			_ifstream.open(_filename.c_str(), ios::in);
			
			if( ! _ifstream.is_open()){
				throw string("Could not create default config file, exiting.");
			}
		}
	}
	
	_ifstream.close();
	_init();
	_filename = filename;
}

Config::~Config(){
	writeConfig();
	
	map<string, ConfigSection*>::iterator iter;
	for(iter = _sections.begin(); iter != _sections.end(); iter++){
		ConfigSection* sec = _sections[iter->first];
		delete sec;
	}
	
	_sections.clear();
}

void Config::_init(){
	ifstream _ifstream(_filename.c_str(), ios::in);
	
	if( ! _ifstream.is_open()){
		_ifstream.close();
		throw string("Could not open configfile ") + _filename;
	}
	
	string _line;
	ConfigSection* _section = 0;
	bool _inSection = false;
	
	while(getline(_ifstream, _line)){
	
		if( ( ! _line.empty()) && _line.at(0) != '#'){
			if( ! _inSection){
				_section = new ConfigSection(_line);
				_inSection = true;
			}else{
				if(_line.at(0) != '{' && _line.at(0) != '}'){
					StringTokenizer st(_line, ' ');
					
					/* Only read the entry if the line has 2 tokens */
					if(st.count() == 2){
						string _setting(st.next());
						string _value(st.next());
						_section->set(_setting, _value);
					}else if(st.count() > 2){
						string _setting(st.next());
						string _value(st.next());
						
						while(st.hasNext()){
							_value.append(" ");
							_value.append(st.next());
						}
						
						_section->set(_setting, _value);
					} // st.count() > 2
				}else{
					if(_line.at(0) == '}'){
						_sections[_section->name()] = _section;
						_inSection = false;
					}
				} // line.at(0) != { && line.at(0) != } 
			}
		} // line != empty && line.at(0) != #
	} // while
	
	_ifstream.close();
	
}

void Config::_writeSection(ofstream* fs, string name){
	if( ! (*fs).is_open()){
		throw string("Could not access file ") + _filename;
	}
	
	ConfigSection* _section = _sections[name];
	map<string, string> _entries = _section->all();
	map<string, string>::iterator it;
	
	(*fs) << endl;
	(*fs) << name << endl;
	(*fs) << "{" << endl;
	
	for(it = _entries.begin(); it != _entries.end(); it++){
		(*fs) << (*it).first << " " << (*it).second << endl;
	}
	
	(*fs) << "}" << endl;
	(*fs) << endl;
}

void Config::_writeDefaultConfig(){
	ofstream myofstream;
	myofstream.open(_filename.c_str(), ios::out | ios::app);
	
	if( ! myofstream.is_open()){
		myofstream.close();
		return;
	}
	
	myofstream << "# README" << endl;
	myofstream << "# This file contains the settings that Skaar uses to run properly." << endl;
	myofstream << endl;
	myofstream << "# Core settings" << endl;
	myofstream << "core" << endl;
	myofstream << "{" << endl;
	myofstream << "realname \"Lazy Foo\"" << endl;
	myofstream << "nick myname__" << endl;
	myofstream << "password foo" << endl;
	myofstream << "ui terminal" << endl;
	myofstream << "defaultui ncurses" << endl;
	myofstream << "}" << endl;
	myofstream << endl;
	myofstream << "# Servers" << endl;
	myofstream << "# Below you can specify which servers to" << endl;
	myofstream << "# connect to when skaar starts. If there" << endl;
	myofstream << "# are no servers specified, you have to " << endl;
	myofstream << "# connect manually." << endl;
	myofstream << "# The format for a server config line" << endl;
	myofstream << "# is as follows:" << endl;
	myofstream << "# <hostname|ip> <port>" << endl;
	
    myofstream << endl;
    myofstream << "servers" << endl;
    myofstream << "{" << endl;
    myofstream << "localhost 6667" << endl;
    myofstream << "}" << endl;
    myofstream << endl;
	myofstream << "# Protocols" << endl;
	myofstream << "# In this section you have to specify the protocol" << endl;
	myofstream << "# for each of the servers mentioned above." << endl;
	myofstream << "# The protocol specification must always be in lowercase," << endl;
	myofstream << "# and the server's name or ip must be an exact match" << endl;
	myofstream << "# To the server mentioned in the servers section." << endl;
	myofstream << "# The format for a protocol config line is as follows:" << endl;
	myofstream << "# <hostname|ip> <protocol>" << endl;
	myofstream << endl;
	myofstream << "protocols" << endl;
	myofstream << "{" << endl;
	myofstream << "localhost rfc1459" << endl;
	myofstream << "}" << endl;
	myofstream << endl;
    myofstream << "# Channels" << endl;
    myofstream << "# You can also specify which channels" << endl;
    myofstream << "# to connect to on startup." << endl;
    myofstream << "# The format for this is as follows," << endl;
    myofstream << "# but has to be the same as the server" << endl;
    myofstream << "# mentioned above." << endl;
    myofstream << "# <server|ip> <channel>" << endl;
    myofstream << endl;
    myofstream << "channels" << endl;
    myofstream << "{" << endl;
    myofstream << "localhost #mychannel" << endl;
    myofstream << "}" << endl;
    myofstream << endl;
    myofstream << "# Message aliases" << endl;
    myofstream << "# You can also add your own aliases here." << endl;
    myofstream << "# The format of a alias line is as follows:" << endl;
    myofstream << "# <alias> <command>" << endl;
    myofstream << endl;
    myofstream << "aliases" << endl;
    myofstream << "{" << endl;
    myofstream << "j JOIN" << endl;
    myofstream << "join JOIN" << endl;
    myofstream << "nick NICK" << endl;
    myofstream << "pass PASS" << endl;
    myofstream << "say PRIVMSG" << endl;
    myofstream << "query PRIVMSG" << endl;
    myofstream << "quit QUIT" << endl;
    myofstream << "exit QUIT" << endl;
    myofstream << "bye QUIT" << endl;
    myofstream << "signoff QUIT" << endl;
    myofstream << "user USER" << endl;
    myofstream << "}" << endl;
    myofstream << endl;
    
    myofstream.close();
}

/* Returns the section that has the provided name */
ConfigSection* Config::getSection(string name){
    map<string, ConfigSection*>::iterator it = _sections.find(name);
    
    if(it == _sections.end()){
	return 0;
    }
    
    return _sections[name];
}

/* Returns the value of the provided setting in setting */
string Config::getValue(string section, string setting){
    map<string, ConfigSection*>::iterator it = _sections.find(section);
    
    if(it == _sections.end()){
	return "";
    }
    
    ConfigSection* scs = _sections[section];
    return scs->get(setting);
}

/* Sets or overwrites a settings' value */
void Config::setSetting(string section, string setting, string value){
    map<string, ConfigSection*>::iterator it = _sections.find(section);
    
    if(it == _sections.end()){
	throw string("Section ") + section + string(" does not exist.");
    }
    
    ConfigSection* scs = _sections[section];
    
    scs->set(setting, value);
}

/* Writes the config to a file */
bool Config::writeConfig(){
    //cout << "DEBUG: Writing config." << endl;
    
    ofstream myofstream(_filename.c_str(), ios::in);
    
    if(myofstream.is_open()){
	myofstream.open(_filename.c_str(), ios::in | ios::out | ios::app | ios::trunc);
    }else{
	myofstream.open(_filename.c_str(), ios::in | ios::out | ios::app);
    }
    
    myofstream << "# README" << endl;
    myofstream << "# This file contains the settings that Skaar uses to run properly." << endl;
    myofstream << endl;
    
    /* The core section */
    try{
	myofstream << "# Core settings" << endl;
	_writeSection(&myofstream, string("core"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    /* The servers section */
    try{
	myofstream << "# Servers" << endl;
	myofstream << "# Below you can specify which servers to" << endl;
	myofstream << "# connect to when skaar starts. If there" << endl;
	myofstream << "# are no servers specified, you have to" << endl;
	myofstream << "# connect manually." << endl;
	myofstream << "# The format for a server config line" << endl;
	myofstream << "# is as follows:" << endl;
	myofstream << "# <hostname|ip> <port>" << endl;
	myofstream << endl;
	
	_writeSection(&myofstream, string("servers"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
	/* The protocols section */
	try{
		myofstream << "# Protocols" << endl;
		myofstream << "# In this section you have to specify the protocol" << endl;
		myofstream << "# for each of the servers mentioned above." << endl;
		myofstream << "# The protocol specification must always be in lowercase," << endl;
		myofstream << "# and the server's name or ip must be an exact match" << endl;
		myofstream << "# To the server mentioned in the servers section." << endl;
		myofstream << "# The format for a protocol config line is as follows:" << endl;
		myofstream << "# <hostname|ip> <protocol>" << endl;
		myofstream << endl;
		
		_writeSection(&myofstream, string("protocols"));
	}catch(string msg){
		cerr << msg << endl;
	}
	
    /* The channels section */
    try{
	myofstream << "# Channels" << endl;
	myofstream << "# You can also specify which channels" << endl;
	myofstream << "# to join at startup." << endl;
	myofstream << "# The format for this is as follows," << endl;
	myofstream << "# but has to be the same as the server" << endl;
	myofstream << "# mentioned above." << endl;
	myofstream << "# <server|ip> <channel>" << endl;
	
	_writeSection(&myofstream, string("channels"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    /* The aliases section */
    try{
	myofstream << "# Mesage aliases" << endl;
	myofstream << "# You can also add you own aliases here." << endl;
	myofstream << "# The format of an alias line is as follows:" << endl;
	myofstream << "# <alias> <command>" << endl;
	
	_writeSection(&myofstream, string("aliases"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    myofstream.close();
    return true;
}

