#ifndef HEADER_H
#define HEADER_H
#define DATA_SZ 512

using namespace std;

#include <stdint.h>
#include <iostream>
#include <bitset>
#include <cstring>

struct packet {
  uint8_t TypeTRWindow;
  uint8_t sequenceNum;
  uint16_t length;
  uint32_t timestamp;
  uint32_t crc1;
  uint32_t crc2;
  char data[DATA_SZ];
};

class Header {
  private:
    struct packet packet;
  public:
    Header();
    unsigned int getType(); // Can be 1,2,3
    unsigned int getTR(); // 0 or 1. Will always be 0
    unsigned int getWindow(); // 0-31
    unsigned int getSequenceNum(); // 0-255
    unsigned int getLength(); // 0-512
    unsigned int getTimestamp(); // 0-2^32-1
    unsigned int getCRC1(); // TODO
    unsigned int getCRC2(); // TODO
    void *getPacket() {
      return &packet;
    }
    std::string getPayload() {
      return packet.data;
    }
    void setType(unsigned int type);
    void setTR(unsigned int tr);
    void setWindow(unsigned int window);
    void setSequenceNum(unsigned int seqNum);
    void setLength(unsigned int length);
    void setTimestamp(unsigned int time);
    void setCRC1(unsigned int crc1); // TODO
    void setCRC2(unsigned int crc2); // TODO
    void setPayload(std::string data);
    void printHeader();
    void printBinary();
};

#endif // HEADER_H