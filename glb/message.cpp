#include "message.hpp"
#include "../compiler.hpp"
#include <string>
#include <iostream>

void message(int i_message = -1, int i_fl_flag = -1, std::string sp_message = "") {
    std::string s_message = "";
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
    -m  --macro             Define macros (-m 'WINDOWS=TRUE')\n\
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
    case ERR_OPEN_FILE:
        s_message = "Error opening file.";
        break;
    case ERR_READ_FILE:
        s_message = "Error reading file.";
        break;
    case ERR_WRITE_FILE:
        s_message = "Error writing file.";
        break;
    case ERR_CLOSE_FILE:
        s_message = "Error closing file.";
        break;
    case MEMORY:
        s_message = "Memory error.";
        break;
    case SYNTAX:
        s_message = "Syntax error.";
        break;
    case INVALID_FILE:
        s_message = "Invalid file.";
        break;
    default:    
        s_message = "Unknown error.";
        break;
    }

    std::cout                                               << 
    "%%%%%%%%%%%%%%%%%% ATL MESSAGE %%%%%%%%%%%%%%%%%%\n"   <<
    "MESSAGE CODE: "                                        <<
    "<"                                                     <<
    i_message                                               <<
    "-"                                                     <<
    i_fl_flag                                               <<
    ">\n"                                                   <<
    "MESSAGE: "                                             <<
    s_message                                               <<
    "\n"                                                    <<
    (sp_message != "" ?
        "GIVEN SP_MESSAGE: <"+sp_message+">"
        : ""
    )                                                       <<
    "\n"                                                    <<
    "%%%%%%%%%%%%%%%%%% END MESSAGE %%%%%%%%%%%%%%%%%%"     <<
    std::endl;
}