/**
 * @file SkaarLog.h
 * @brief Logging class for Skaar
 *
 * Copyright (c) 2008 Coen Bijlsma
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SKAARLOG_H
#define SKAARLOG_H

#include <string>
#include <vector>

using namespace std;

class SkaarLog {
private:
	
	string _filename;
	vector<string> _entries;
	
	/*
	 * Initializes the logfile for use.
	 * Actually, it appends .%Y-%m-%d to the filename.
	 */
	void _init();
	
	/*
	 * Returns the date/time (or both) in the
	 * provided format. Format options are
	 * the parameters available to strftime.
	 * @see man strftime(3)
	 */
	string _getDateTime(string);

public:
	/*
	 * The loglevels available to SkaarLog
	 */
	enum loglevel_t {LOG_DEBUG = 0, LOG_ERROR, LOG_WARNING, LOG_INFO};
	
	/*
	 * Constructor.
	 * Sets _filename to skaar.log
	 */
	SkaarLog();
	
	/*
	 * Constructor.
	 */
	SkaarLog(string logfile);
	
	/*
	 * Destructor.
	 * Writes the entries to the logfile before
	 * destroying the object.
	 */
	virtual ~SkaarLog();
	
	/*
	 * Appends the log to the vector of entries, including
	 * the date and time that the log was appended.
	 */
	void append(string log, loglevel_t severity = LOG_INFO);
	
	/*
	 * Convenience method for the char* lovers among us.
	 * Effectively calls append(string log, loglevel_t severity);
	 */
	void append(const char* log, loglevel_t severity = LOG_INFO);
	
	/*
	 * Tries to write the entries to the logfile.
	 * After writing the entries to the logfile, the
	 * vector containing the entries is cleared.
	 */
	bool save();
	
	/*
	 * Returns a vector of strings containing the 
	 * available entries.
	 * Note that if the log had been saved, the entries 
	 * saved don't exist anymore in the vector, so it's possible
	 * that this method returns an empty vector, although
	 * you might expect otherwise.
	 */
	vector<string> getEntries();
	
};

#endif /* SKAARLOG_H */
