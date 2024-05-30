#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>

Token look_ahead(std::vector<Token> &tokens, int &amount);
Token look_behind(std::vector<Token> &tokens, int &amount);

void syntaxanalysis(std::vector<Token> &tokens) {
    std::vector<Parse_Expression> parsetree;
    for(size_t cur_ind = 0; cur_ind < tokens.size(); cur_ind++){
        // std::cout << "Type: '" << tokens[cur_ind].type << "' Subtype: '" << tokens[cur_ind].subtype << "' Value: '" << tokens[cur_ind].value << "'" << std::endl;
        switch (tokens[cur_ind].type){
        case Tokens::KEYWORD:
            std::cout << "Keyword: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::OPERATOR: 
            std::cout << "Operator: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::SEPARATOR: 
            std::cout << "Separator: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::LITERAL: 
            std::cout << "Literal: " << tokens[cur_ind].value << std::endl;
            switch (tokens[cur_ind].subtype){
            case Literal_Tokens::INT_LITERAL: 
                break;
            case Literal_Tokens::FLOAT_LITERAL: 
                break;
            case Literal_Tokens::STRING_LITERAL: 
                break;
            case Literal_Tokens::CHAR_LITERAL: 
                break;
            case Literal_Tokens::BOOL_LITERAL: 
                break;
            default:
                message(UNKNOWN_TOKEN, FL_compiler3, 
                "Unknown literal subtype: " + 
                std::to_string(tokens[cur_ind].subtype) + 
                " value: " + 
                tokens[cur_ind].value + 
                " at line: " + 
                std::to_string(tokens[cur_ind].line) + 
                " column: " + 
                std::to_string(tokens[cur_ind].column), 
                true);
                break;
            }
            break;
        case Tokens::IDENTIFIER: 
            std::cout << "Identifier: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::COMMENT: 
            std::cout << "Comment: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::PREPROCESSOR: 
            std::cout << "Preprocessor: " << tokens[cur_ind].value << std::endl;
            break;
        case Tokens::WHITESPACE: 
            std::cout << "Whitespace: " << tokens[cur_ind].value << std::endl;
            break;
        default: 
            message(UNKNOWN_TOKEN, FL_compiler3, "Unknown token type: " + std::to_string(tokens[cur_ind].type) + " subtype: " + std::to_string(tokens[cur_ind].subtype), true);
            break;
        }
    }
}

Token look_ahead(std::vector<Token> &tokens, size_t &amount){
    return tokens[amount + 1];
}

Token look_behind(std::vector<Token> &tokens, size_t &amount){
    return tokens[amount - 1];
}
