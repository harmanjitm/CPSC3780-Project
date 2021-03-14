#ifndef SENDER_H
#define SENDER_H

using namespace std;

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class sender {
  public:
    int createSocket();
    bool parseArguments(int argc, char *argv[]);
    void send(int socket, const void *packet_data, int size);
    void error(string message);
    void setPort(int toSet);
    void setHost(char* toSet);
    void setDatafile(char* toSet);
    int getPort();
    char* getHost();
    char* getDatafile();
  private:
    int port;
    char* host;
    char* datafile;
};

#endif // SENDER_H