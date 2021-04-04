#include "../include/sender.h"

/**
 * Send a packet using UDP protocol through an established socket ID, packet data, and packet size.
 * 
 * @param socket The socket ID to send the data through.
 * @param packet_data The packet information/data to be sent.
 * @param size The size of the packet/data to be transmitted.
 */
void sender::sendPacket(int socket, const void *packet_data, int size) {
  // Construct the socket - Vars
  struct sockaddr_in sock_address;
  sock_address.sin_family = AF_INET;

  // Set host and port
  inet_pton(AF_INET, host, &sock_address.sin_addr.s_addr);
  sock_address.sin_port = htons(port);

  // Send data
  int sent = sendto(socket, packet_data, size, 0, (sockaddr*)&sock_address, sizeof(sock_address));

  // Make sure the packets were sent
  if (sent < size) {
    error("Failed to send packets.");
  }
  cout << "=================================" << "\n\n";
  cout << "----Waiting to receive packets---\n";
  
  // Wait and receive packet
  socklen_t addr_len;
  addr_len = sizeof sock_address;
  int bytes = recvfrom(socket, &packet_data, size, 0, (struct sockaddr*)&sock_address, &addr_len);
  if (bytes == -1) {
    error("Failed to receive Ack packets.");
  }
}

/**
 * Creates socket with the given host and port using the commandline args.
 * The socket is checked for errors to ensure it is open.
 * A cerr is thrown if the socket is not open.
 * A value of the sock_num is returned.
 * 
 * @return The socket number
 */
int sender::makeSocket() {
  int status = -1;
  struct sockaddr_in server;

  // Create a socket
  sock_num = socket(AF_INET, SOCK_DGRAM, 0);

  // Check the socket
  if (sock_num < 0) {
    error("Could not open socket.");
  }

  cout << "Socket established on: " << getHost() << "/" << getPort() << "\n";
  return sock_num;
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

void sender::error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

/**
 * Set the SocketID
 * 
 * @param toSet The SocketID to set.
 */
void sender::setSocketNum(int toSet) {
  sock_num = toSet;
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
bool sender::parseCMD(int argc, char *argv[]) {
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
    sendPacket(sock_num, buf, fileLength);
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
int sender::getSocketNum() {
  return sock_num;
}
