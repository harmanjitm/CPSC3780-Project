#include "../include/receiver.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sys/time.h>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

bool receiver::parseCMD(int argc, char *argv[]) {
  if (argc == 4 && strcmp(argv[1], "-f") == 0) {
    datafile = argv[2];
    setPort(argv[3]);
  } else if (argc == 2) {
    setPort(argv[1]);
  } else {
    error("Invalid number of arguments.");
  }
}

char* receiver::getPort() {
  return port;
}

void receiver::setPort(char* toSet) {
  port = toSet;
}

/**
 * Get the DataFile
 * 
 * @return The Datafile.
 */
char* receiver::getDatafile() {
  return datafile;
}

void receiver::setDatafile(char* toSet) {
  datafile = toSet;
}

void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void receiver::connectToSender() {
  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv;
  int numbytes;
  struct sockaddr_storage their_addr;
  char* buf[MAXBUFLEN];
  socklen_t addr_len;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;  // set to AF_INET to use IPv4
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;  // use default IP

  if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
    error("Error getting address information.");
  }

  // loop through all the results and bind to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      error("Could not find a socket.");
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      error("Failed to bind to any sockets.");
    }
    break;
  }

  if (p == NULL) {
    error("Failed to bind socket.");
  }
  freeaddrinfo(servinfo);

  // Continue looping and receiving packets
  cout << "\n----------Listening For Packets on Port: " << port << "----------" << "\n";
  while(true) {
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
      error("Failed to receive packet successfully.");
    }

    printf("Connection: Got packet from %s\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
    printf("Received: Packet is %d bytes long\n", sizeof(packet));
    buf[numbytes] = '\0';
    printHeader();

    // Send a response back after changing type to Ack - 2
    setType(2);
    int numSent = sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
    if (numSent == -1) {
      error("Failed to send a Ack response.");
    }
    cout << "Response: Sequence #" << (int)packet.sequenceNum << " Ack sent.\n";
  }

  close(sockfd);
}

void receiver::error(string message) {
  cerr << "Error: " << message << "\n";
  exit(1);
}

void receiver::printHeader() {
  cout << "Type: " << "\t\t" << getType() << "\n";
  cout << "TR: " << "\t\t" << getTR() << "\n";
  cout << "Window: " << "\t" << getWindow() << "\n";
  cout << "Sequence Num: " << "\t" << (int) packet.sequenceNum << "\n";
  cout << "Length: " << "\t" << (int) packet.length << "\n";
  cout << "Timestamp: " << "\t" << packet.timestamp << "\n";
  printf("Payload: \t%c\n", packet.data);
  cout << "Total Size: " << "\t" << sizeof(packet) << "\n";
  cout << "-------------------------------------------------------\n\n";
  string s;
  stringstream ss;
  ss << packet.data;
  ss >> s;
  cout << s;
  int millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  cout << "Time current: " << millisec_since_epoch << "\n";
  cout << "Time receive: " << packet.timestamp << "\n";
  cout << "Time to receive packet (ms): " << millisec_since_epoch - packet.timestamp << "\n";
}

unsigned int receiver::getType() {
  return (packet.TypeTRWindow >> 6);
}

unsigned int receiver::getTR() {
  uint8_t temp = packet.TypeTRWindow;
  temp = temp << 2;
  temp = temp >> 7;
  return temp;
}

unsigned int receiver::getWindow() {
  uint8_t temp = packet.TypeTRWindow;
  temp = temp << 3;
  temp = temp >> 3;
  return temp;
}

uint8_t changeBit(unsigned int end, int pos, int toChange) {
  uint8_t m = 1 << pos;
  return ((end & ~m) | (toChange << pos));
}

void receiver::setType(unsigned int type) {
  uint8_t temp = packet.TypeTRWindow;
  if (type == 1) {
    temp = changeBit(temp, 6, 1);
    temp = changeBit(temp, 7, 0);
    packet.TypeTRWindow = temp;
  } else if (type == 2) {
    temp = changeBit(temp, 6, 0);
    temp = changeBit(temp, 7, 1);
    packet.TypeTRWindow = temp;
  } else if (type == 3) {
    temp = changeBit(temp, 6, 1);
    temp = changeBit(temp, 7, 1);
    packet.TypeTRWindow = temp;
  }
}