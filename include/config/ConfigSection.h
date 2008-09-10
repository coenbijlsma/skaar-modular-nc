/**
 * @file ConfigSection.h
 * @brief A section in a configfile
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

	/*
	 * Constructor.
	 */
	ConfigSection(string name);
	
	/*
	 * Destructor. Does nothing at this time.
	 */
	virtual ~ConfigSection();
	
	/*
	 * Returns the name of this ConfigSection
	 */
	string name();
	
	/*
	 * Returns the value of the requested setting.
	 * If the setting does not exist, an empty
	 * string is returned.
	 */
	string get(string setting);
	
	/*
	 * Sets or creates the setting with the
	 * provided value.
	 */
	void set(string setting, string value);
	
	/*
	 * Returns all the entries for this ConfigSection.
	 */
	map<string, string> all();
};

#endif /* CONFIGSECTION_H */
