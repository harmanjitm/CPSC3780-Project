# CPSC3780 Project
## Harmanjit M, Aaron A.

## How to compile and run the Sender
- From the command line in the working directory of `./sender/`, run the following command: `make`
- The sender will be compiled into the `/build/` directory.
- In order to run the program, run the following command `./build/sender [-f datafile.txt] host port`
- Example with file: `./build/sender -f ../test.txt 127.0.0.1 64341`
- Example: `./build/sender 127.0.0.1 64341`

## How to compile and run the Receiver
- From the command line in the working directory of `./receiver/`, run the following command: `g++ -o receiver receiver.cpp`
- In order to run the program, run the following command `./receiver [-f datafile.txt] port`
- Example: `./receiver 64341`

## How to compile and run tests
- From the command line in the working directory of `./sender/`, run the following command: `make test`
- Now that the test's are compiled, we can run it using the following command from the current directory: `./a.out`