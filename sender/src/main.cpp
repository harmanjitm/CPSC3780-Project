#include "../include/sender.h"
#include "../include/Header.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sys/time.h>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

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
  string data;

  // cout << "Packet: " << h.getPacket() << "packet";

  // Check arguments and create socket on localhost/127.0.0.1
  bool isDataFile = s.parseCMD(argc, argv);
  int net_socket = s.makeSocket();

  // Infinite loop to send messages if no datafile is passed in
  while(!isDataFile) {
    cin >> data;
    h.setPayload(data);
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    h.setTimestamp(millisec_since_epoch);
    h.setLength(sizeof(data));
    cout << "\n\n\n-----------Sent packet-----------" << "\n\n";
    h.printHeader();
    s.sendPacket(net_socket, h.getPacket(), sizeof(h.getPacket()));
    cout << "Did not receive ACK packet in time for seq #" << h.getSequenceNum() << "\n";
    cout << "Retransmitting sequence: " << h.getSequenceNum() << "\n";
    h.setSequenceNum(h.getSequenceNum()+1);
  }

  // TODO 
  if(isDataFile) {
    cout << "Sent file.\n";
  }

  // End program
  return 0;
}