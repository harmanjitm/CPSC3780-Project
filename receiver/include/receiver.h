#ifndef RECEIVER_H
#define RECEIVER_H
#define MAXBUFLEN 556
#define DATA_SZ 512

using namespace std;

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

struct packet {
  uint8_t TypeTRWindow;
  uint8_t sequenceNum;
  uint16_t length;
  uint32_t timestamp;
  uint32_t crc1;
  uint32_t crc2;
  char data[DATA_SZ];
};

class receiver {
  private:
    char* port;
    int sock_num;
    char* datafile;
    struct packet packet;
  public:
    bool parseCMD(int argc, char *argv[]);
    void connectToSender();
    void sendAck(int seqNum);
    void error(string message);
    char* getPort();
    char* getDatafile();
    void setType(unsigned int type);
    void setPort(char* toSet);
    void setDatafile(char* toSet);
    void parseHeader(char header);
    unsigned int getType(); // Can be 1,2,3
    unsigned int getTR(); // 0 or 1. Will always be 0
    unsigned int getWindow(); // 0-31
    void printHeader();
    void *getPacket() {
      return &packet;
    }
};

#endif // RECEIVER_H