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
    int makeSocket();
    bool parseCMD(int argc, char *argv[]);
    void sendPacket(int socket, const void *packet_data, int size);
    void error(string message);
    void setPort(int toSet);
    void setHost(char* toSet);
    void setDatafile(char* toSet);
    void setSocketNum(int toSet);
    int getPort();
    char* getHost();
    char* getDatafile();
    int getSocketNum();
  private:
    int port;
    char* host;
    char* datafile;
    int sock_num;
};

#endif // SENDER_H