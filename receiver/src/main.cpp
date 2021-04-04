#include "../include/receiver.h"

#include <fstream>
#include <iostream>

int port = 64341;
receiver r;

int main(int argc, char *argv[]) {
  bool writeToFile = r.parseCMD(argc, argv);
  r.connectToSender();
}