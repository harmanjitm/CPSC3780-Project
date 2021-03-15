#include "../include/sender.h"

#include <fstream>
#include <iostream>

string host = "127.0.0.1";
int port = 64341;
sender s;

int main(int argc, char *argv[]) {
  char* data;

  // Check arguments and create socket on localhost/127.0.0.1
  bool isDataFile = s.parseCMD(argc, argv);
  int net_socket = s.makeSocket();

  // Infinite loop to send messages if no datafile is passed in
  while(!isDataFile) {
    cin >> data;
    s.sendPacket(net_socket, data, sizeof(data));
    cout << "Sent: " << data << "\n";
  }

  if(isDataFile) {
    cout << "Sent file.\n";
  }

  // End program
  return 0;
}