#include "../include/sender.h"

void sender::error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

void sender::parseArgs(int argc, char *argv[]) {
  // Check and see if arguments are appropriate
  if (argc != 3 && argc != 5) {
    error("Invalid number of arguments.");
  }
  
  // Takes in a datafile
  if (argc == 5) {
    setDatafile(argv[2]);
    setHost(argv[3]);
    setPort(atoi(argv[4]));
  }

  // No datafile - Only Host & Port
  if (argc == 3) {
    setHost(argv[1]);
    setPort(atoi(argv[2]));
  }
}

int sender::createSocket() {
  int status = -1;
  int net_socket;
  struct sockaddr_in server;

  // Create a socket
  net_socket = socket(AF_INET, SOCK_DGRAM, 0);

  // Check the socket
  if (net_socket < 0) {
    error("Could not open socket.");
  }
  
  // Address for the socket to connect to
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;

  // Create connection and check status
  status = bind(net_socket, (struct sockaddr*) &server, sizeof(server));

  if(status == -1) {
    error("Could not establish a connection with the socket.");
  } else {
    cout << "Status: " << status << "\n";
  }
}

void sender::setPort(int toSet) {
  port = toSet;
}

void sender::setHost(string toSet) {
  host = toSet;
}

void sender::setDatafile(string toSet) {
  datafile = toSet;
}

int sender::getPort() {
  return port;
}

string sender::getHost() {
  return host;
}

string sender::getDatafile() {
  return datafile;
}

/* 
 * Receiver
 * int status = connect(net_socket, (struct sockaddr *) &server, sizeof(server)); 
*/
