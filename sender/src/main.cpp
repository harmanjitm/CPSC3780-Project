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
  h.setType(3);
  h.setTR(0);
  h.setWindow(31);
  h.setLength(DATA_SZ);
  h.setTimestamp(std::time(NULL));
  h.setPayload("Test Payload");
  h.printHeader();
  char* data;

  // cout << "Packet: " << h.getPacket() << "packet";

  // Check arguments and create socket on localhost/127.0.0.1
  bool isDataFile = s.parseCMD(argc, argv);
  int net_socket = s.makeSocket();

  // Infinite loop to send messages if no datafile is passed in
  while(!isDataFile) {
    cin >> data;
    // h.setPayload(data);
    s.sendPacket(net_socket, data, sizeof(data));
    cout << "Sent: " << data << "\n";
  }

  if(isDataFile) {
    cout << "Sent file.\n";
  }

  // End program
  return 0;
}