#include "../include/Header.h"

Header::Header() {
  packet.TypeTRWindow = 255;
}

unsigned int getBit(unsigned int num, int bitAmount, int position) {
  return (((1 << bitAmount) -1) & (num >> (position - 1)));
}

unsigned int Header::getType() {
  return (packet.TypeTRWindow >> 6);
  // unsigned int temp = packet.TypeTRWindow;
  // std::cout << "Value: " << temp << "\n";
  // // Get first two bits of header

  // std::bitset<8> x(temp);
  // std::cout << "Value: " << x << "\n";
  // temp = getBit(temp, 7, 5);
  // std::cout << "Type: " << temp << "\n";
  // std::bitset<8> t(temp);
  // std::cout << "Type: " << t << "\n";
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

}

unsigned int Header::getLength() {

}

unsigned int Header::getTimestamp() {

}

unsigned int Header::getCRC1() {

}

unsigned int Header::getCRC2() {

}

void Header::printHeader() {
  cout << "Type: " << "\t\t" << getType() << "\n";
  cout << "TR: " << "\t\t" << getTR() << "\n";
  cout << "Window: " << "\t" << getWindow() << "\n";
  cout << "Sequence Num: " << "\t" << getSequenceNum() << "\n";
  cout << "Length: " << "\t" << getLength() << "\n";
  cout << "Timestamp: " << "\t" << getTimestamp() << "\n";
  cout << "CRC1: " << "\t\t" << getCRC1() << "\n";
  cout << "CRC2: " << "\t\t" << getCRC2() << "\n";
}