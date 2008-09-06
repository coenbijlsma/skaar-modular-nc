#ifndef ABSTRACTPROTOCOL_H
#define ABSTRACTPROTOCOL_H

#include <string>
#include <vector>
#include "AbstractMessage.h"

using namespace std;

class AbstractProtocol {
	
	virtual ~AbstractProtocol(){}
	
	/*
	 * Returns a vector containing the registered
	 * messages for this protocol.
	 */
	virtual vector<string> registeredMessages() =0;
	
	/*
	 * Registers a message to this protocol.
	 * Returns true if this succeeded, and false
	 * if it doesn't (for example, if the message
	 * already is registered).
	 */
	virtual bool registerMessage(string message) =0;
	
	/*
	 * Unregisters the provided message at this protocol.
	 * Returns true if that succeeded, and false otherwise.
	 */
	virtual bool unregisterMessage(string message) =0;
	
	/*
	 * Returns whether the provided message is 
	 * registered at this protocol.
	 */
	virtual bool isRegistered(string message) =0;
	
	/*
	 * Tries to translate a raw string from the SkaarSocket
	 * to a decent AbstractMessage. 
	 * Returns the AbstractMessge* on success, and 
	 * (AbstractMessage*)0 if it fails.
	 */
	virtual AbstractMessage* translateIncoming(string raw) =0;
	
	/*
	 * Returns a string formatted following this protocol.
	 * The raw string is supposed to be the user input,
	 * so this is actually the way to translate user input
	 * and send it awayyyyy.
	 */
	virtual string toProtocolString(string raw) =0;
};

#endif
