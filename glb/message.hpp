#pragma once
#include <string>

#define FL_compiler1            1
#define FL_compiler2            2
#define FL_compiler3            3
#define FL_compiler4            4
#define FL_compiler5            5
#define FL_compiler6            6
#define FL_compiler7            7
#define FL_compiler8            8

#define NO_ARGUMENTS            1
#define HELP                    2
#define VERSION                 3
#define NO_INPUT                4
#define NO_OUTPUT               5
#define REDEFINITION            6
#define NO_INPUT_OUTPUT         7
#define ERR_OPEN_FILE           8
#define ERR_READ_FILE           9
#define ERR_WRITE_FILE          10
#define ERR_CLOSE_FILE          11
#define MEMORY                  12
#define TOKENIZER_SYNTAX        13
#define INVALID_FILE            14

void message(int i_message, int i_fl_flag, std::string sp_message, bool fatal);