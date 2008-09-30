#include "NickMessage.h"
#include "StringTokenizer.h"

const string NickMessage::COMMAND = "NICK";

NickMessage::NickMessage(RFC1459* protocol, string raw){
	_raw = raw;
	_protocol = protocol;
	_init();
}

NickMessage::~NickMessage(){}

void NickMessage::_init(){

	/* Check if the raw message is empty */
	if(_raw.empty()){
		throw string("Empty message");
	}
	
	StringTokenizer st(_raw, ' ');
	int paramcount = (st.count() -1); // because the command doesn't count
	
	/* Do we have a prefix? */
	if(_raw[0] == ':'){
		_prefix = st.next();
		paramcount--; // Because the prefix was also in st.count()
	}
	
	/* And also, do we have at least the minimum amount of parameters? */
	if(paramcount < MINPARAMS){
		throw string("Not enough parameters supplied in message ") + _raw;
	}
	
	/* Check if the message really is an PASS message */
	if(st.next().substr(1) != COMMAND){
		throw string("Not a(n) ") + COMMAND + string(" message: ") + _raw;
	}
	
	/* Read the parameters */
	for(int i = 0; st.hasNext(); i++){
		_params.push_back(st.next());
	}
}

string NickMessage::getPrefix(){
	return _prefix;
}

string NickMessage::getSenderNick(){
	string retval;

	if(_prefix.length() > 0){
		
	}
	
	return retval;
	
}

string NickMessage::getCommand(){
	return COMMAND;
}

string NickMessage::getReceiver(){
	return string("");
}

unsigned int NickMessage::getMinParams(){
	return MINPARAMS;
}

/* %pr = prefix, %cmd = command, %par = params */
string NickMessage::format(string format = ""){
	if(format != ""){
		string::size_type pr_loc = format.find("%pr", 0);
		if(pr_loc != string::npos){
			format.replace(pr_loc, 3, _prefix, _prefix.length(), _prefix.length());
		}

		string::size_type cmd_loc = format.find("%cmd", 0);
		if(cmd_loc != string::npos){
			format.replace(cmd_loc, 4, COMMAND, COMMAND.length(), COMMAND.length());
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

			format.replace(par_loc, 4, params, params.length(), params.length());
			return format;
		}
	}else{
		string params;
		for(int i = 0; i < _params.size(); i++){
			if(i > 0){
				params.append(" ");
			}
			params.append(_params.at(i));
		}
		return params;
		
	}
		
}

vector<string> NickMessage::getParams(){
	return _params;
}

RFC1459* NickMessage::getProtocol(){
	return _protocol;
}
