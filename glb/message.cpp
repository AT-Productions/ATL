#include "message.hpp"
#include "../compiler.hpp"
#include <string>
#include <iostream>

void message(int i_message = -1, int i_fl_flag = -1) {
    std::string s_message = "EMPTY";
    int FL_FLAG = -1;
    switch (i_message) {
    case NO_ARGUMENTS:
        s_message = "No arguments given. --help for more information.";
        break;
    case HELP:
        s_message = 
"\
ATL {OPTIONS | ARGUMENTS}\n\
ARGUMENTS:\n\
    -i, --input             Input file(s), enclose in quotes for multiple files\n\
    -o, --output            Output file\n\
\n\
OPTIONS:\n\
    -h, --help              Display this information\n\
    -v, --version           Display the current version\n\
\n\
";
        break;
    case VERSION:
        s_message = "Current ATL version: " + 
                                    std::to_string(VERSION_MAJOR) + "." + 
                                    std::to_string(VERSION_MINOR) + "." + 
                                    std::to_string(VERSION_PATCH) + "." + 
                                    std::to_string(VERSION_BUILD);
        break;
    case NO_INPUT:
        s_message = "No input file specified.";
        break;
    case NO_OUTPUT:
        s_message = "No output file specified.";
        break;
    case REDEFINITION:
        s_message = "Redefinition of argument.";
        break;
    case NO_INPUT_OUTPUT:
        s_message = "No input or output file specified.";
        break;
    }

    std::cout   << 
    "%%%%%%%%%%%%%%%%%% ATL MESSAGE %%%%%%%%%%%%%%%%%%\n" <<
    "MESSAGE CODE: " <<
    "<"         <<
    i_message   <<
    "-"         <<
    i_fl_flag   <<
    ">\n"        <<
    s_message   <<
    std::endl;
}