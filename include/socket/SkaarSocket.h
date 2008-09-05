/*
comment
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
    
public:
  SkaarSocket(char* host, int port);
  virtual ~SkaarSocket();
  
  bool connected();
  bool createConnection();
  bool disconnect();
  bool sendMessage(string msg);
  string readMessage();
  int pollConnection();
  
};

#endif /* SKAARSOCKET_H */
