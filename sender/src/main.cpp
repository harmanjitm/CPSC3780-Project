#include "../include/sender.h"
#include "../include/Header.h"

#include <fstream>
#include <iostream>
#include <ctime>

string host = "127.0.0.1";
int port = 64341;
sender s;

int main(int argc, char *argv[]) {
  Header h;
  h.setType(1);
  h.setTR(0);
  h.setWindow(31);
  h.setSequenceNum(1);
  h.setLength(DATA_SZ);
  h.setTimestamp(std::time(NULL));
  h.setPayload("Test Payload");
  cout << "Size: " << sizeof(h.getPacket()) << "\n";
  string data;

  // cout << "Packet: " << h.getPacket() << "packet";

  // Check arguments and create socket on localhost/127.0.0.1
  bool isDataFile = s.parseCMD(argc, argv);
  int net_socket = s.makeSocket();

  // Infinite loop to send messages if no datafile is passed in
  while(!isDataFile) {
    cin >> data;
    h.setPayload(data);
    h.setLength(sizeof(data));
    cout << "\n\n\n-----------Sent packet-----------" << "\n\n";
    h.printHeader();
    s.sendPacket(net_socket, h.getPacket(), sizeof(h.getPacket()));
    cout << "Received Ack for Sequence #" << h.getSequenceNum() << "\n";
    h.setSequenceNum(h.getSequenceNum()+1);
  }

  // TODO 
  if(isDataFile) {
    cout << "Sent file.\n";
  }

  // End program
  return 0;
}