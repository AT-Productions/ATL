#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//    KEYWORD: int, string, return
//    IDENTIFIER: main, arg, printf
//    OPERATOR: +, -, *, /, =, +=, -=, ==, !=, >, <, >=, <=
//    SEPARATOR: ;, {, }, (, )
//    LITERAL: 1
//    COMMENT: //, /* */
//    PREPROCESSOR: #include, #define, #pragma, #ifdef, #ifndef, #endif, #ifdef, #error


void Parser(std::vector<std::string> &s_arguments) {
    // Read file line by line, char by char
    std::ifstream file(s_arguments[INPUT], std::ios::binary);
    if (!file.is_open()) {
        message(ERR_OPEN_FILE, FL_compiler2);
        exit(ERR_OPEN_FILE);
    } else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    
    }
}

std::string look_ahead()
{
    return "";
}