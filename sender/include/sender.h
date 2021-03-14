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

class sender {
  public:
    int createSocket();
    void parseArgs(int argc, char *argv[]);
    void error(string message);
    void setPort(int toSet);
    void setHost(string toSet);
    void setDatafile(string toSet);
    int getPort();
    string getHost();
    string getDatafile();
  private:
    int port;
    string host;
    string datafile;
};

#endif // SENDER_H