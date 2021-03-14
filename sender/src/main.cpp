#include "../include/sender.h"

string datafile = "";
string host = "127.0.0.1";
int port = 64341;
sender s;

int main(int argc, char *argv[]) {
  s.parseArgs(argc, argv);
  s.createSocket();
}