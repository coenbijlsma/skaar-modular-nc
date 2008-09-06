#include "AdminMessage.h"
#include "StringTokenizer.h"

AdminMessage::AdminMessage(RFC1459* protocol, string raw){
	_raw = raw;
	_protocol = protocol;
	_init();
}

AdminMessage::~AdminMessage(){}

void AdminMessage::_init(){

	/* Check if the raw message is empty */
	if(_raw.empty()){
		throw string("Empty message");
	}
	
	StringTokenizer st(_raw, ' ');
	string tmp;
	
	if(st.count() < MINPARAMS){
		throw string("Not enough parameters supplied in message ") + _raw;
	}
	
	/* Check if the message really is an ADMIN message */
	if(st.next().substr(1) != COMMAND){
		throw string("Not a(n) ") + COMMAND + string(" message: ") + _raw;
	}
	
	/* Read the parameters */
	for(int i = 0; st.hasNext(); i++){
		_params.push_back(st.next());
	}
}

string AdminMessage::getPrefix(){
	return string;
}

string AdminMessage::getCommand(){
	return COMMAND;
}

unsigned int AdminMessage::getMinParams(){
	return MINPARAMS;
}

/* %pr = prefix, %cmd = command, %par = params */
string AdminMessage::format(string format){
	string::size_type pr_loc = format.find("%pr", 0);
	if(pr_loc != string::npos){
		format.replace(pr_loc, 3, _prefix, _prefix.length());
	}
	
	string::size_type cmd_loc = format.find("%cmd", 0);
	if(cmd_loc != string::npos){
		format.replace(cmd_loc, 4, COMMAND, COMMAND.length());
	}
	
	string::size_type par_loc = format.find("%par", 0);
	if(par_loc != string::npos){
		string params;
		for(int i = 0; i < _params.size(); i++){
			if( i > 0){
				params.append(" ");
			}
			params.append(_params.at(i));
		}
		
		format.replace(par_loc, 4, params, params.length());
	}
	
	return format;
}

vector<string> AdminMessage::getParams(){
	return _params;
}

RFC1459* AdminMessage::getProtocol(){
	return _protocol;
}
