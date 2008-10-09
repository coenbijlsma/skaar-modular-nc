/**
 * @file JoinCommand.h
 * @brief The command that registers the user at the server.
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

#ifndef JOINCOMMAND_H
#define JOINCOMMAND_H

#include <string>
#include "AbstractCommand.h"
#include "CommandHandler.h"
#include "SkaarLog.h"

using namespace std;

/*
 * Syntax: /join <channel>
 */
class JoinCommand : public AbstractCommand {
private:
	CommandHandler* _handler;
	SkaarLog* _log;
	string _command;
	string _raw;
	string _server;
	int _port;
	string _proto;
	
public:
	static const string COMMAND; // JOIN
	static const int MINPARAMS = 1;
	static const int MAXPARAMS = 3;
	
	/*
	 * @brief Constructor
	 */
	JoinCommand(SkaarLog* log, string raw);
	
	/*
	 * @brief Destructor
	 */
	virtual ~JoinCommand();
	
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

#endif /* JOINCOMMAND_H */
