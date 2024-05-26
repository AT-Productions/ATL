#pragma once
// #include <string>

#define FL_compiler1            1
#define FL_compiler2            2

#define NO_ARGUMENTS            0
#define HELP                    1
#define VERSION                 2
#define NO_INPUT                3
#define NO_OUTPUT               4
#define REDEFINITION            5
#define NO_INPUT_OUTPUT         6
#define ERR_OPEN_FILE           7

void message(int i_message, int i_fl_flag);