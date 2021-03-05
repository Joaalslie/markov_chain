# Discrete-Time Markov Chain data Structure
## About the project
This project consist of an implementation of a data structure that resembles Markov Chains
in discrete time. The entire source code is written in C. The data structure mainly visualizes
transitioning between different states within a markov chain. The path can also be logged and
written to a text file.

## Input file
The main program takes in a json-file as parameter during execution. The json-file needs to contain
the dimensionality (**num_dim**) of the matrix which represents the markov chain, as well as the matrix 
itself. The matrix (**matrix**) has to be written as a single-dimensional array (using 2D arrays would
have been easier, I know..). The elements in the array are parsed row-wise (see the example files 
included). The final element in the file is the start-value (**start**), which denotes which denotes
the initial state in the chain.

## Output file
The output file is a simple text file that will contain the state history, meaning that each transition
is logged.

## Example applications
### Main program
The Main Program parses the json-file and creates a markov chain according to the matrix in the file.
It then runs for 100 iterations and logs all transitions between states in the file. The states are also
printed to the user in the terminal, but is also logged to the text file provided as argument to the program.

### Weather program
The weather program utilizes the markov chain data structure to simulate weather changes in discreet time.
This is a common case that is used when explaining markov chains. For this case, it maps the 3 possible states
in the markov chain to a weather type, then makes transitions based on user input and prints out the weather
which the current state represents.

## Compiling
Before compiling the program, make sure that json-c-dev is installed. </br>

Use the following command to compile the main program:
```
$ gcc main.c markov_chain.c markov_chain.h list.c list.h json_parser.c json_parser.h -ljson-c -o <program_name>
```
Use the following command to compile the weather application:
```
$ gcc weather.c markov_chain.c markov_chain.h list.c list.h json_parser.c json_parser.h -ljson-c -o <program_name>
```

## Running
Use the following command To run the main program:
```
$ ./<program_name> <json_file> <log_file>
```

Use the following command to run the weather application: 
```
$ ./<program_name> <json_file>
```
