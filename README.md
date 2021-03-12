# CPSC3780 Project
## Harmanjit M, Aaron A.

## How to compile and run the Sender
- From the command line in the working directory of `./sender/`, run the following command: `g++ -o sender sender.cpp`
- In order to run the program, run the following command `./sender [-f datafile.txt] host port`
- Example: `./sender 127.0.0.1 64341`

## How to compile and run the Receiver
- From the command line in the working directory of `./receiver/`, run the following command: `g++ -o receiver receiver.cpp`
- In order to run the program, run the following command `./receiver [-f datafile.txt] port`
- Example: `./receiver 64341`