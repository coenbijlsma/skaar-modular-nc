#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include "AbstractProtocol.h"
#include <string>
#include <vector>

using namespace std;

class AbstractMessage {

	virtual ~AbstractMessage(){}
	
	/*
	 * Returns the prefix that belongs to this
	 * message, if any.
	 * If no prefix is available, this method
	 * should return an empty string.
	 */
	virtual string getPrefix() =0;
	
	/*
	 * Returns the nick of the sender of 
	 * the message.
	 */
	virtual string getSenderNick() =0;
	
	/*
	 * Returns the receiver of the message.
	 */
	virtual string getReceiver() =0;
	
	/*
	 * Returns the command of this message, 
	 * say PRIVMSG
	 */
	virtual string getCommand() =0;
	
	/*
	 * Returns the minimum amount of parameters
	 * required for this message.
	 */
	virtual unsigned int minParams() =0;
	
	/*
	 * Returns a string formatted according to the
	 * given format string.
	 * No specific format is mandatory here, because 
	 * you need to create your own implementation anyway.
	 */
	virtual string format(string format) =0;
	
	/*
	 * Returns the parameters that go with the message.
	 */
	virtual vector<string> getParams() =0;
	
	/*
	 * Returns the protocol this message belongs to.
	 */
	virtual AbstractProtocol* getProtocol() =0;
	
};

#endif
