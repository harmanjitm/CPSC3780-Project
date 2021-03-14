#include "../include/sender.h"

void sender::error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

// Return true if its a file
bool sender::parseArguments(int argc, char *argv[]) {
  // Check and see if arguments are appropriate
  if (argc != 3 && argc != 5) {
    error("Invalid number of arguments.");
  }
  
  // Takes in a datafile
  if (argc == 5 && strcmp(argv[1], "-f") == 0) {
    setDatafile(argv[2]);
    setHost(argv[3]);
    setPort(atoi(argv[4]));
    return true;
  }

  // No datafile - Only Host & Port
  if (argc == 3) {
    setHost(argv[1]);
    setPort(atoi(argv[2]));
  }

  return false;
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
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  // Create connection and check status
  status = bind(net_socket, (struct sockaddr*) &server, sizeof(server));

  if(status < 0) {
    error("Could not establish a connection with the socket.");
  }

  cout << "Socket established on: " << getHost() << "/" << getPort() << "\n";
  return net_socket;
}

void sender::send(int socket, const void *packet_data, int size) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;

  // Set host and port
  inet_pton(AF_INET, host, &addr.sin_addr.s_addr);
  addr.sin_port = htons(port);

  // Send data
  int sent = sendto(socket, packet_data, size, 0, (sockaddr*)&addr, sizeof(addr));

  if (sent < size) {
    error("Failed to send packets.");
  }
}

void sender::setPort(int toSet) {
  port = toSet;
}

void sender::setHost(char* toSet) {
  host = toSet;
}

void sender::setDatafile(char* toSet) {
  datafile = toSet;
}

int sender::getPort() {
  return port;
}

char* sender::getHost() {
  return host;
}

char* sender::getDatafile() {
  return datafile;
}

/* 
 * Receiver
 * int status = connect(net_socket, (struct sockaddr *) &server, sizeof(server)); 
*/
