/**
 * @file SkaarConfig.h
 * @brief Representation of a configfile
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

#ifndef SKAARCONFIG_H
#define SKAARCONFIG_H

#include "SkaarConfigSection.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class SkaarConfig {
private:
	string _filename;
	map<string, SkaarConfigSection*> _sections;
	
	/*
	 * Tries to read the configfile and fill
	 * the _sections map.
	 * @throws string If the configfile could not
	 * be opened.
	 */
	void _init();
	
	/*
	 * Writes the content of _sections[name] to
	 * _fs.
	 * @throws string If the ofstream* is not open.
	 */
	void _writeSection(ofstream* _fs, string name);
	
	/*
	 * Writes a default configfile.
	 * This happens when the configfilename
	 * provided to the constructor does not exist, 
	 * and the standard configfile does not either.
	 */
	void _writeDefaultConfig();

public:
	
	/*
	 * Constructor.
	 * Tries to open the provided configfile
	 * and then calls _init() to read its contents.
	 * If the provided configfile does not exist,
	 * this constructor tries the default configfile.
	 * If that doesn's exist either, it tries to write
	 * the default configfile, and _init() with that.
	 * If that also fails, it gives up all hope and
	 * stops.
	 * @throws string If all hope has gone.
	 */
	SkaarConfig(string filename = "skaar.conf.default");
	
	/*
	 * Writes the current config to the configfile, and
	 * cleans up the map of sections, effectively calling
	 * their destructors.
	 */
	virtual ~SkaarConfig();
	
	/*
	 * Looks for the requested SkaarConfigSection.
	 * Returns it if it exists, otherwise returns
	 * a (SkaarConfigSection*)0 pointer.
	 */
	SkaarConfigSection* getSection(string name);
	
	/*
	 * Tries to locate the requested section and setting.
	 * If either doesn't exist, this function returns an
	 * empty string.
	 * Otherwise calls get() on the SkaarConfigSection.
	 * @see SkaarConfigSection.h
	 */
	string getValue(string section, string setting);
	
	/*
	 * Sets or creates a setting in the requested section.
	 * Of the section does not exist, an error occurs.
	 * @throws string If the requested section does not
	 * exist.
	 */
	void setSetting(string section, string setting, string value);
	
	/*
	 * Tries to write the current config to the configfile.
	 * In fact this function always returns true, but I will
	 * to work on that, promise.
	 */
	bool writeConfig();
	
};

#endif /* CONFIG_H */
