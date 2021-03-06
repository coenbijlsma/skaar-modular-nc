/**
 * @file ConnectCommand.h
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

#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include <string>
#include "AbstractCommand.h"
#include "SkaarCallbackHandler.h"
#include "SkaarLog.h"

using namespace std;

/*
 * Syntax: /connect <server> [<port> [proto=rfc1459]]
 * The port is only optional if the server is
 * defined in the config-file. The protocol is always
 * optional, but defaults to rfc1459.
 */
class ConnectCommand : public AbstractCommand {
private:
	SkaarCallbackHandler* _handler;
	SkaarLog* _log;
	string _command;
	string _raw;
	string _server;
	int _port;
	string _proto;
	
public:
	static const string COMMAND; // CONNECT
	static const int MINPARAMS = 1;
	static const int MAXPARAMS = 3;
	
	/*
	 * @brief Constructor
	 */
	ConnectCommand(SkaarLog* log, string raw);
	
	/*
	 * @brief Destructor
	 */
	virtual ~ConnectCommand();
	
	/*
	 * @brief Returns the command.
	 */
	string getCommand();
	
	/*
	 * @brief Sets the SkaarCallbackHandler.
	 * This actually is an instance of Skaar, 
	 * but with limited possibilities, because you don't
	 * need them all here.
	 */
	void setCallbackHandler(SkaarCallbackHandler* handler);
	
	/*
	 * @brief Executes the Command.
	 * Executes the command, and returns whether it 
	 * succeeded or not.
	 * The exact reason why the execution failed
	 * if execute() returns false is logged.
	 */
	bool execute();
};

#endif /* CONNECTCOMMAND_H */
