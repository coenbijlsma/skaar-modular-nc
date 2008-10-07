/**
 * @file CommandFactory.h
 * @brief Creates commands out of raw strings
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

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "AbstractCommand.h"
#include "SkaarLog.h"

using namespace std;

class CommandFactory {
public:

	/*
	 * @brief Translates the given raw string to an AbstractCommand*
	 * Returns the AbstractCommand* that can be factored from the raw
	 * string.
	 * If the string doesn't start with a forward slash (/), 
	 * an (AbstractCommand*)0 is returned.
	 * This also happens if the command isn't recognized.
	 */
	static AbstractCommand* translate(SkaarLog* log, string raw);
};

#endif /* COMMANDFACTORY_H */
