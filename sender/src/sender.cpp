#include "../include/sender.h"

void sender::error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

/**
 * Parse the command line arguments and transmit a file if necessary.
 * -f specifies the file to transmit. Otherwise no file is transmitted.
 * 
 * The number of arguments to be specified are 3 or 5.
 * 
 * 3 Arguments are for transmitting messages
 * 5 Arguments for transmitting a file
 * 
 * @param argc The number of arguments
 * @param argv The elements in the arguments
 * 
 * @return true if arguments are transmitting a datafile. Else false.
 */
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

    // Get file information for sending
    ifstream file(datafile, std::ios::binary);
    file.seekg(0, std::ios::end);
    size_t fileLength = file.tellg();
    file.seekg(0, std::ios::beg);

    char buf[fileLength];
    file.read(buf, fileLength);

    // Send file
    send(socketID, buf, fileLength);
    return true;
  }

  // No datafile - Only Host & Port
  if (argc == 3) {
    setHost(argv[1]);
    setPort(atoi(argv[2]));
    return false;
  }

  return false;
}

/**
 * Creates socket with the given host and port using the commandline args.
 * The socket is checked for errors to ensure it is open.
 * A cerr is thrown if the socket is not open.
 * A value of the socketID is returned.
 * 
 * @return The socket ID
 */
int sender::createSocket() {
  int status = -1;
  struct sockaddr_in server;

  // Create a socket
  socketID = socket(AF_INET, SOCK_DGRAM, 0);

  // Check the socket
  if (socketID < 0) {
    error("Could not open socket.");
  }
  
  // Address for the socket to connect to
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  // Create connection and check status
  status = bind(socketID, (struct sockaddr*) &server, sizeof(server));

  if(status < 0) {
    error("Could not establish a connection with the socket.");
  }

  cout << "Socket established on: " << getHost() << "/" << getPort() << "\n";
  return socketID;
}

/**
 * Send a packet using UDP protocol through an established socket ID, packet data, and packet size.
 * 
 * @param socket The socket ID to send the data through.
 * @param packet_data The packet information/data to be sent.
 * @param size The size of the packet/data to be transmitted.
 */
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

/**
 * Set the port
 * 
 * @param toSet The new Port to set.
 */
void sender::setPort(int toSet) {
  port = toSet;
}

/**
 * Set the host
 * 
 * @param toSet The new Host to set.
 */
void sender::setHost(char* toSet) {
  host = toSet;
}

/**
 * Set the DataFile
 * 
 * @param toSet The DataFile to set.
 */
void sender::setDatafile(char* toSet) {
  datafile = toSet;
}

/**
 * Set the SocketID
 * 
 * @param toSet The SocketID to set.
 */
void sender::setSocketID(int toSet) {
  socketID = toSet;
}

/**
 * Get the Port
 * 
 * @return The Port which is being used.
 */
int sender::getPort() {
  return port;
}

/**
 * Get the Host
 * 
 * @return The Host which is being used.
 */
char* sender::getHost() {
  return host;
}

/**
 * Get the DataFile
 * 
 * @return The Datafile.
 */
char* sender::getDatafile() {
  return datafile;
}

/**
 * Get the SocketID
 * 
 * @return The socketID
 */
int sender::getSocketID() {
  return socketID;
}
