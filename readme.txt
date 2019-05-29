Before compiling the program, install json-c-dev.
This can be done in Linux by running:
    $ sudo apt install libjson-c

To compile the code, 
run:
    $ gcc main.c markov_chain.c markov_chain.h list.c list.h json_parser.c json_parser.h -ljson-c -o <insert program name here>

to run the program,
run:
    $ ./<insert program name here> <insert json file here> <insert name of the file to write to here>