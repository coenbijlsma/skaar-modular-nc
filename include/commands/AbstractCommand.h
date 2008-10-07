/**
 * @file AbstractCommand.h
 * @brief Abstraction for commands in Skaar
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

#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include "CommandHandler.h"
#include <string>

using namespace std;

class AbstractCommand {
public:

	/*
	 * @brief Destructor
	 */
	virtual ~AbstractCommand(){}
	
	/*
	 * @brief Returns the command
	 * Returns a string containing the command,
	 * I.E. CONNECT for the ConnectCommand.
	 */
	virtual string getCommand() =0;
	
	/*
	 * @brief Sets the CommandHandler
	 * The CommandHandler can provide information to the command
	 * when it is executed.
	 */
	virtual void setCommandHandler(CommandHandler* handler) =0;
	
	/*
	 * @brief Executes the command.
	 * See the headerfiles of the implementations
	 * for more details like exceptions and stuff.
	 */
	virtual bool execute() =0;
};

#endif /* ABSTRACTCOMMAND_H */
