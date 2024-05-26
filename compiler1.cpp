#include <iostream>
#include <vector>
#include "glb/message.hpp"
#include "compiler.hpp"


void main(int argc, char* argv[]){
    std::vector<std::string> s_arguments(S_ARG_SIZE);
    
    if(argc < 2){
        message(NO_ARGUMENTS, FL_compiler1);
        exit(NO_ARGUMENTS);
    }

    bool b_output = false;
    bool b_input = false;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            message(HELP, FL_compiler1);
            exit(HELP);
        }
        else if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0){
            message(VERSION, FL_compiler1);
            exit(VERSION);
        }
        else if(strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-i") == 0){
            if(b_input){
                message(REDEFINITION, FL_compiler1);
                exit(REDEFINITION);
            }
            if(i + 1 >= argc){
                message(NO_INPUT, FL_compiler1);
                exit(NO_INPUT);
            }
            s_arguments[INPUT] = argv[i + 1];
            i++;
            b_input = true;
        }
        else if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0){
            if(b_output){
                message(REDEFINITION, FL_compiler1);
                exit(REDEFINITION);
            }
            if(i + 1 >= argc){
                message(NO_OUTPUT, FL_compiler1);
                exit(NO_OUTPUT);
            }
            s_arguments[OUTPUT] = argv[i + 1];
            i++;
            b_output = true;
        }
    }

    if(!b_input){
        message(NO_INPUT, FL_compiler1);
        exit(NO_INPUT);
    }
    if (!b_output){
        message(NO_OUTPUT, FL_compiler1);
        exit(NO_OUTPUT);
    }

    Parser(s_arguments);
    
    exit(-1);
}