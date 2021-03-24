#include "../include/Header.h"

void error(string message) {
  cerr << "Error: " << message << "\n";
}

Header::Header() {
  packet.TypeTRWindow = 0;
  packet.sequenceNum = 0;
  packet.length = DATA_SZ;
  packet.timestamp = 0;
  packet.crc1 = 0;
  packet.crc2 = 0;
}

uint8_t changeBit(unsigned int end, int pos, int toChange) {
  uint8_t m = 1 << pos;
  return ((end & ~m) | (toChange << pos));
}

unsigned int Header::getType() {
  return (packet.TypeTRWindow >> 6);
}

unsigned int Header::getTR() {
  uint8_t temp = packet.TypeTRWindow;
  temp = temp << 2;
  temp = temp >> 7;
  return temp;
}

unsigned int Header::getWindow() {
  uint8_t temp = packet.TypeTRWindow;
  temp = temp << 3;
  temp = temp >> 3;
  return temp;
}

unsigned int Header::getSequenceNum() {
  return packet.sequenceNum;
}

unsigned int Header::getLength() {
  return packet.length;
}

unsigned int Header::getTimestamp() {
  return packet.timestamp;
}

unsigned int Header::getCRC1() {
  return packet.crc1;
}

unsigned int Header::getCRC2() {
  return packet.crc2;
}

void Header::setType(unsigned int type) {
  uint8_t temp = packet.TypeTRWindow;
  if (type == 1) {
    temp = changeBit(temp, 6, 1);
    temp = changeBit(temp, 7, 0);
    packet.TypeTRWindow = temp;
  } else if (type == 2) {
    temp = changeBit(temp, 6, 0);
    temp = changeBit(temp, 7, 1);
    packet.TypeTRWindow = temp;
  } else if (type == 3) {
    temp = changeBit(temp, 6, 1);
    temp = changeBit(temp, 7, 1);
    packet.TypeTRWindow = temp;
  }
}

void Header::setTR(unsigned int tr) {
  packet.TypeTRWindow = changeBit(packet.TypeTRWindow, 5, tr);
}

void Header::setWindow(unsigned int window) {
  if (window >=0 && window <=31) {
    packet.TypeTRWindow >> 5;
    packet.TypeTRWindow << 5;
    packet.TypeTRWindow ^= window;
  } else {
    error("Invalid window");
  }
}

void Header::setSequenceNum(unsigned int seqNum) {
  packet.sequenceNum = seqNum;
}

void Header::setLength(unsigned int length) {
  packet.length = length;
}

void Header::setTimestamp(unsigned int time) {
  packet.timestamp = time;
}

void Header::setCRC1(unsigned int crc1) {
  packet.crc1 = crc1;
}

void Header::setCRC2(unsigned int crc2) {
  packet.crc2 = crc2;
}

void Header::setPayload(std::string data) {
  strcpy(packet.data, data.c_str());
}

void Header::printHeader() {
  cout << "Type: " << "\t\t" << getType() << "\n";
  cout << "TR: " << "\t\t" << getTR() << "\n";
  cout << "Window: " << "\t" << getWindow() << "\n";
  cout << "Sequence Num: " << "\t" << getSequenceNum() << "\n";
  cout << "Length: " << "\t" << getLength() << "\n";
  cout << "Timestamp: " << "\t" << getTimestamp() << "\n";
  cout << "Payload: " << "\t" << getPayload() << "\n";
  cout << "CRC1: " << "\t\t" << getCRC1() << "\n";
  cout << "CRC2: " << "\t\t" << getCRC2() << "\n";
}
