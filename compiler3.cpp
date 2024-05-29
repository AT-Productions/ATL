#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>

void syntaxanalysis(std::vector<Token> &tokens) {
    for(auto &token : tokens){
        // std::cout << "Type: '" << token.type << "' Subtype: '" << token.subtype << "' Value: '" << token.value << "'" << std::endl;
        std::cout << "Type: " << token.type << " Subtype: " << token.subtype << " Value: " << token.value << "" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << token.value << std::endl;
        std::cout << std::endl;
    }
}