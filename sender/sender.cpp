using namespace std;

#include <iostream>

int main(int argc, char *argv[]) {
  // Check and see if arguments are appropriate
  if (argc != 3 && argc != 5) {
    cout << "Invalid number of arguments.\n";
  }
  
  // Takes in a datafile
  if (argc == 5) {
    // Check for file
  }

  // No datafile - Only Host & Port
  if (argc == 3) {
    cout << "Host: " << argv[1] << "\n";
    cout << "Port: " << argv[2] << "\n";
  }
}
