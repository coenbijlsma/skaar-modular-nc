/**
 * @file ExitCommand.h
 * @brief The command that exits from Skaar.
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

#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include <string>
#include "AbstractCommand.h"
#include "CommandHandler.h"
#include "SkaarLog.h"

using namespace std;

/*
 * Syntax: /exit
 */
class ExitCommand : public AbstractCommand {
private:
	CommandHandler* _handler;
	SkaarLog* _log;
	string _command;
	string _raw;
	
public:
	static const string COMMAND; // EXIT
	static const int MINPARAMS = 0;
	static const int MAXPARAMS = 0;
	
	/*
	 * @brief Constructor
	 */
	ExitCommand(SkaarLog* log, string raw);
	
	/*
	 * @brief Destructor
	 */
	virtual ~ExitCommand();
	
	/*
	 * @brief Returns the command.
	 */
	string getCommand();
	
	/*
	 * @brief Sets the CommandHandler.
	 * This actually is an instance of Skaar, 
	 * but with limited possibilities, because you don't
	 * need them all here.
	 */
	void setCommandHandler(CommandHandler* handler);
	
	/*
	 * @brief Executes the Command.
	 * Executes the command, and returns whether it 
	 * succeeded or not.
	 * The exact reason why the execution failed
	 * if execute() returns false is logged.
	 */
	bool execute();
};

#endif /* EXITCOMMAND_H */
