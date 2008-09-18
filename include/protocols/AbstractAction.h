/**
 * @file AbstractAction.h
 * @brief Abstraction interface for actions to be carried out by Skaar
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

#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <string>

using namespace std;

class AbstractAction {
public:
	
	virtual ~AbstractAction() {}
	virtual string getAction() =0;
	virtual bool execute() =0;
};

#endif /* ABSTRACTACTION_H */
