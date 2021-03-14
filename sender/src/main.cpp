#include "../include/sender.h"

#include <fstream>
#include <iostream>

string host = "127.0.0.1";
int port = 64341;
sender s;

int main(int argc, char *argv[]) {
  char* data;

  // Check arguments and create socket on localhost/127.0.0.1
  bool isDataFile = s.parseArguments(argc, argv);
  int net_socket = s.createSocket();

  // Infinite loop to send messages if no datafile is passed in
  while(!isDataFile) {
    cin >> data;
    s.send(net_socket, data, sizeof(data));
    cout << "Sent: " << data << "\n";
  }

  // Get file information for sending
  ifstream file(s.getDatafile(), std::ios::binary);
  file.seekg(0, std::ios::end);
  size_t fileLength = file.tellg();
  file.seekg(0, std::ios::beg);

  char buf[fileLength];
  file.read(buf, fileLength);

  // Send file
  s.send(net_socket, buf, fileLength);
  cout << "Sent file: " << s.getDatafile() << "\n";

  // End program
  return 0;
}