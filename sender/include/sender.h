#ifndef SENDER_H
#define SENDER_H

using namespace std;

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
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
    void setSocketID(int toSet);
    int getPort();
    char* getHost();
    char* getDatafile();
    int getSocketID();
  private:
    int port;
    char* host;
    char* datafile;
    int socketID;
};

#endif // SENDER_H