#include "SkaarSocket.h"

SkaarSocket::SkaarSocket(char* host, int port){
	_port = port;
	struct hostent* h = gethostbyname(host);

	if(h == 0){
		_host = host;
	}else{
		_host = inet_ntoa(*((struct in_addr*)h->h_addr));
	}	

	_connected = false;
	_pollTimeoutMSecs = 0;
}

SkaarSocket::~SkaarSocket(){
	if(_connected){
		disconnect();
	}
}

bool SkaarSocket::connected(){
	return _connected;
}

bool SkaarSocket::createConnection(){
	if( (_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return false;
	}

	memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = inet_addr(_host);

	if(connect(_sockfd, (struct sockaddr*)&_addr, sizeof(_addr)) == -1){
		close(_sockfd);
		perror("connect");
		return false;
	}

	_connected = true;

	/* Setup polling */
	_pfd[0].fd = _sockfd;
	_pfd[0].events = POLLRDNORM;
  
	return true;
}

bool SkaarSocket::disconnect(){
	if( ! _connected){
		return false;
	}
	
	if(shutdown(_sockfd, SHUT_RDWR) == -1){
		perror("shutdown (during disconnect)");
		return false;
	}
	
	_connected = false;
	
	if(close(_sockfd) == -1){
		_sockfd = 0; // just to be sure
		perror("close");
		return false;
	}
	
	return true;
}

bool SkaarSocket::sendMessage(string msg){
	int bytes_sent;
	
	if( ! _connected){
		fprintf(stderr, "Not connected.\n");
		return false;
	}
	
	if(msg[strlen(msg.c_str())] != '\0'){
		msg += '\0';
	}
	
	if( (bytes_sent = send(_sockfd, msg.c_str(), strlen(msg.c_str()), 0)) == -1 
		|| bytes_sent != strlen(msg.c_str()) ){
		perror("send");
		return false;
	}
	
	return true;
}

string SkaarSocket::readMessage(){
	int msglen;
	if( ! _connected){
		fprintf(stderr, "Not connected.\n");
		return string("");
	}
	
	char* temp_msg = (char*)malloc(513);
	memset(temp_msg, 0, 513);
	
	while(strlen(temp_msg) <= 512){
		char* chars = (char*)malloc(513);
		memset(chars, 0, 513);
		
		switch(recv(_sockfd, chars, 512, 0)){
			case 0:
				return '\0';
			case -1:
				perror("recv");
				return '\0';
			default:
				strcat(temp_msg, chars);
		}
		
		msglen = strlen(temp_msg);
		break;
	}
	
	return string(temp_msg);
}

int SkaarSocket::pollConnection(){
	return poll(_pfd, 1, _pollTimeoutMSecs);
}
