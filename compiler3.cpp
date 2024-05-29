#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>

Token look_ahead(std::vector<Token> &tokens, int &amount);
Token look_behind(std::vector<Token> &tokens, int &amount);

void syntaxanalysis(std::vector<Token> &tokens) {
    for(uint16_t cur_ind = 0; cur_ind < tokens.size(); cur_ind++){
        std::cout << "Type: '" << tokens[cur_ind].type << "' Subtype: '" << tokens[cur_ind].subtype << "' Value: '" << tokens[cur_ind].value << "'" << std::endl;
        switch (tokens[cur_ind].type){
        case Tokens::KEYWORD:
            break;
        case Tokens::OPERATOR: 
            break;
        case Tokens::SEPARATOR: 
            break;
        case Tokens::LITERAL: 
            break;
        case Tokens::IDENTIFIER: 
            break;
        case Tokens::COMMENT: 
            break;
        case Tokens::PREPROCESSOR: 
            break;
        case Tokens::WHITESPACE: 
            break;
        default: 
            message(UNKNOWN_TOKEN, FL_compiler3, "Unknown token type: " + std::to_string(tokens[cur_ind].type) + " subtype: " + std::to_string(tokens[cur_ind].subtype), true);
            break;
        }
    }
}

Token look_ahead(std::vector<Token> &tokens, int &amount){
    return tokens[amount + 1];
}

Token look_behind(std::vector<Token> &tokens, int &amount){
    return tokens[amount - 1];
}
