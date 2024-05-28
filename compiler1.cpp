#include <iostream>
#include <vector>
#include "glb/message.hpp"
#include "compiler.hpp"

/*+++

Argument handling: Parses command line arguments.                                 - compiler1.cpp
Lexical Analysis: Breaks source code into tokens.                                 - compiler2.cpp
Syntax Analysis: Checks tokens against grammar and creates a parse tree.          - compiler3.cpp
Semantic Analysis: Verifies logical consistency and annotates the tree.           - compiler4.cpp
Intermediate Code Generation: Converts the annotated tree to intermediate code.   - compiler5.cpp
Optimization: Enhances intermediate code efficiency.                              - compiler6.cpp
Code Generation: Converts optimized intermediate code to machine code.            - compiler7.cpp
Code Linking: Combines all machine code into a final executable.                  - compiler8.cpp

---*/

int main(int argc, char* argv[]){
    std::vector<std::string> s_arguments(S_ARG_SIZE);
    
    if(argc < 2){
        message(NO_ARGUMENTS, FL_compiler1, "");
        exit(NO_ARGUMENTS);
    }

    bool b_output = false;
    bool b_input = false;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            message(HELP, FL_compiler1, "");
            exit(HELP);
        }
        else if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0){
            message(VERSION, FL_compiler1, "");
            exit(VERSION);
        }
        else if(strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-i") == 0){
            if(b_input){
                message(REDEFINITION, FL_compiler1, "redefinition of input file or flag.");
                exit(REDEFINITION);
            }
            if(i + 1 >= argc){
                message(NO_INPUT, FL_compiler1, "--input flag given without a file.");
                exit(NO_INPUT);
            }
            std::string fn = argv[i + 1];
            if(fn.substr(fn.find_last_of(".")) != ".atl"){
                message(INVALID_FILE, FL_compiler1, "invalid file type: " + fn);
                exit(INVALID_FILE);
            }
            s_arguments[INPUT] = fn;
            i++;
            b_input = true;
        }
        else if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0){
            if(b_output){
                message(REDEFINITION, FL_compiler1, "redefinition of output file or flag.");
                exit(REDEFINITION);
            }
            if(i + 1 >= argc){
                message(NO_OUTPUT, FL_compiler1, "--output flag given without a file.");
                exit(NO_OUTPUT);
            }
            s_arguments[OUTPUT] = argv[i + 1];
            i++;
            b_output = true;
        }
        else if(strcmp(argv[i], "--macro") == 0 || strcmp(argv[i], "-m") == 0){
            if(i + 1 >= argc){
                message(NO_INPUT, FL_compiler1, "--macro flag given without a macro.");
                exit(NO_INPUT);
            }
        }
    }

    if(!b_input){
        message(NO_INPUT, FL_compiler1, "No input file specified.");
        exit(NO_INPUT);
    }
    if (!b_output){
        message(NO_OUTPUT, FL_compiler1, "No output file specified.");
        exit(NO_OUTPUT);
    }

    // compiler2.cpp
    std::vector<Token> *tokens = lexanalysis(s_arguments);
    // for(auto token : *tokens){
    //     std::cout << "Type: '" << token.type << "' Subtype: '" << token.subtype << "' Value: '" << token.value << "'" << std::endl;
    // }
    // compiler3.cpp
    syntaxanalysis(*tokens);
    
    delete tokens;
    tokens = nullptr;
    exit(0);
}