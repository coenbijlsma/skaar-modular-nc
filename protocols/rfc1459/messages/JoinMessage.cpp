#include "JoinMessage.h"
#include "StringTokenizer.h"

const string JoinMessage::COMMAND = "JOIN";

JoinMessage::JoinMessage(RFC1459* protocol, string raw){
	_raw = raw;
	_protocol = protocol;
	_init();
}

JoinMessage::~JoinMessage(){}

void JoinMessage::_init(){

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

string JoinMessage::getPrefix(){
	return _prefix;
}

string JoinMessage::getSenderNick(){
	string retval;

	if(_prefix.length() > 0){
		
	}
	
	return retval;
	
}

string JoinMessage::getReceiver(){
	return string("");
	// XXX todo
}

string JoinMessage::getCommand(){
	return COMMAND;
}

unsigned int JoinMessage::minParams(){
	return MINPARAMS;
}

/* %pr = prefix, %cmd = command, %par = params */
string JoinMessage::format(string format = ""){
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

vector<string> JoinMessage::getParams(){
	return _params;
}

RFC1459* JoinMessage::getProtocol(){
	return _protocol;
}
