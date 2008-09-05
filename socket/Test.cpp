#include <string>
#include <iostream>
#include "SkaarSocket.h"

using namespace std;

void show_usage(string programname){
	cout << "Usage: " << programname << " <host> <port>" << endl;
}

int main(int argc, char** argv){
	
	if(argc != 3){
		show_usage(string(argv[0]));
		return 0;
	}
	
	cout << "Testing socket on host " << argv[1] << " at port " << argv[2] << endl;
	
	SkaarSocket* sock = new SkaarSocket(argv[1], atoi(argv[2]));
	
	if(sock->createConnection()){
		printf("Connected.\n");
		if(sock->disconnect()){
			printf("Disconnected.\n");
		}
	}
	
	delete sock;
	return 0;
}
