#include "../include/sender.h"

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

  // Create a socket
  int net_socket;
  net_socket = socket(AF_INET, SOCK_DGRAM, 0);

  // Check the socket
  if (net_socket < 0) {
    error("Could not open socket.");
  }
  
  // Address for the socket to connect to
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;

  /* 
   * Receiver
   * int status = connect(net_socket, (struct sockaddr *) &server, sizeof(server)); 
   */

  // Create connection and check status
  int status = bind(net_socket, (struct sockaddr*) &server, sizeof(server));

  if(status == -1) {
    error("Could not establish a connection with the socket.");
  } else {
    cout << "Status: " << status << "\n";
  }
}
