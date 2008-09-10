/**
 * @file SkaarSocket.h
 * @brief The socket connection for any implemented protocol
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

#ifndef SKAARSOCKET_H
#define SKAARSOCKET_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <poll.h>

using namespace std;

class SkaarSocket {
private:
	struct sockaddr_in _addr;
	struct pollfd _pfd[1];
	int _sockfd;
	int _port;
	int _pollTimeoutMSecs;
	bool _connected;
	char* _host;
	string _protocol;
	
public:

	/*
	 * Constructor.
	 * The host can be either an hostname or an ip-address.
	 * The port speaks for itself, I think.
	 * The protocol has to be the protocol as defined in the
	 * configfile (probably skaar.conf or skaar.conf.default).
	 */
	SkaarSocket(char* host, int port, string protocol = "rfc1459");
	
	/*
	 * Destructor.
	 * Disconnects if still connected.
	 */
	virtual ~SkaarSocket();
  
	/*
	 * Returns whether the socket is connected.
	 */
	bool connected();
	
	/*
	 * Tries to connect to the server.
	 * Returns true on success, false on failure.
	 */
	bool createConnection();
	
	/*
	 * Tries to disconnect the socket.
	 * Returns true on success, false on failure.
	 */
	bool disconnect();
	
	/*
	 * Sends the string over the socket.
	 * Returns true on success, false on failure.
	 */
	bool sendMessage(string msg);
	
	/*
	 * Reads the next message from the socket.
	 * Messages must have some kind of identifier
	 * for the end of message, so enter that here
	 * as well.
	 */
	string readMessage(string delim);
	
	/*
	 * polls the socket for data.
	 * @see man 3 poll.
	 */
	int pollConnection();
	
	/*
	 * Returns the protocol of the server
	 * this socket sends and receives to and from.
	 */
	string getProtocol();
  
};

#endif /* SKAARSOCKET_H */
