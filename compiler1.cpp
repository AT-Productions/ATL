#include <iostream>
#include <vector>
#include "glb/message.hpp"
#include "compiler.hpp"


int main(int argc, char* argv[]){
    std::vector<std::string> s_arguments(2);
    
    if(argc < 2){
        message(NO_ARGUMENTS, FL_compiler1);
        return 1;
    }

    bool b_output = false;
    bool b_input = false;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            message(HELP, FL_compiler1);
            exit(0);
        }
        else if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0){
            message(VERSION, FL_compiler1);
            exit(0);
        }
        else if(strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-i") == 0){
            if(b_input){
                message(REDEFINITION, FL_compiler1);
                return 1;
            }
            if(i + 1 >= argc){
                message(NO_INPUT, FL_compiler1);
                return 1;
            }
            s_arguments[INPUT] = argv[i + 1];
            i++;
            b_input = true;
        }
        else if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0){
            if(b_output){
                message(REDEFINITION, FL_compiler1);
                return 1;
            }
            if(i + 1 >= argc){
                message(NO_OUTPUT, FL_compiler1);
                return 1;
            }
            s_arguments[OUTPUT] = argv[i + 1];
            i++;
            b_output = true;
        }
    }

    if(!b_input){
        message(NO_INPUT, FL_compiler1);
        return 1;
    }
    if (!b_output){
        message(NO_OUTPUT, FL_compiler1);
        return 1;
    }
    
    return 0;
}