using namespace std;

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


string datafile = "";
string host = "127.0.0.1";
int port = 64341;

void error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

int main(int argc, char *argv[]) {
  // Check and see if arguments are appropriate
  if (argc != 3 && argc != 5) {
    error("Invalid number of arguments.");
  }
  
  // Takes in a datafile
  if (argc == 5) {
    datafile = argv[2];
    port = atoi(argv[4]);
  }

  // No datafile - Only Host & Port
  if (argc == 3) {
    cout << "Host: " << argv[1] << "\n";
    cout << "Port: " << argv[2] << "\n";
    port = atoi(argv[2]);
  }

  // Construct the sockets
  int sock;
  int length;
  int incoming_length;
  struct sockaddr_in server;
  struct sockaddr_in receiver;
  char buffer[1024];

  sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (socket < 0) {
    error("Could not open socket.");
  }

  length = sizeof(server);
  // memset((&server), '\0', (length), 0);
}
