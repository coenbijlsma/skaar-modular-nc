#include "SkaarLog.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <stdlib.h>

SkaarLog::SkaarLog(){
	_filename = "skaar.log";
	_init();
}

SkaarLog::SkaarLog(string filename){
	_filename = filename;
	_init();
}

SkaarLog::~SkaarLog(){
	if(_entries.size() > 0){
		if( ! save() ){
			cerr << "ERROR: Some log entries have not been saved because of an error." << endl;
		}
	}
}

void SkaarLog::_init(){
	_filename.append(".");
	_filename.append(_getDateTime(string("%Y%m%d")));
}

string SkaarLog::_getDateTime(string format = "%Y-%m-%d %H:%M:%S"){
	time_t t_time = time(0);
	char c_time[256];
	strftime(c_time, sizeof(c_time), format.c_str(), localtime(&t_time));
	return string(c_time);
}

void SkaarLog::append(string log, loglevel_t severity){
	ostringstream _entry;
	
	_entry << _getDateTime() << "\t" << severity << "\t" << log;
	_entries.push_back(_entry.str());
}

void SkaarLog::append(const char* log, loglevel_t severity){
	append(string(log), severity);
}

bool SkaarLog::save(){
	ofstream outfile(_filename.c_str(), ios::out | ios::app);
	
	if( ! outfile){
		cerr << "Could not open logfile." << endl;
		return false;
	}
	
	for(int i = 0; i < _entries.size(); i++){
		outfile << _entries.at(i) << endl;
	}
	
	outfile.close();
	
	_entries.clear();
	return true;
}

vector<string> SkaarLog::getEntries(){
	return _entries;
}
