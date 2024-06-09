#include "compiler.hpp"
#include "./glb/message.hpp"
#include "./funcs/funcs.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <optional>

std::shared_ptr<Token> look_ahead(std::vector<Token> &tokens, size_t &amount, const size_t &forward = 1){
    return std::make_shared<Token>(tokens[amount + forward]);
}

std::shared_ptr<Token> look_behind(std::vector<Token> &tokens, size_t &amount, const size_t &behind = 1){
    return std::make_shared<Token>(tokens[amount - behind]);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void syntaxanalysis(std::vector<Token> &tokens) {
    std::vector<std::shared_ptr<Parsed_Token>> parsetree;

    size_t cur_inda = 0;
#ifdef DEBUG
    for(size_t i = 0; i < tokens.size(); i++){
        std::cout << "Type: '" << tokens[i].type << "' Subtype: '" << tokens[i].subtype << "' Value: '" << tokens[i].value << "'" << std::endl;
    }
#endif


    for(size_t cur_ind = 0; cur_ind < tokens.size(); cur_ind++){
        switch (tokens[cur_ind].type){
        case Tokens::KEYWORD:
            switch (tokens[cur_ind].subtype){
            case Keyword_Tokens::KEYWORD_EXIT: 
                {
                    const std::shared_ptr<Parsed_Token> _exit = parse_common_function(tokens, cur_ind);
                    parsetree.push_back(_exit);
                }
                break;
            case Keyword_Tokens::KEYWORD_IF: break;
            case Keyword_Tokens::KEYWORD_ELSE: break;
            case Keyword_Tokens::KEYWORD_WHILE: break;
            case Keyword_Tokens::KEYWORD_FOR: break;
            case Keyword_Tokens::KEYWORD_RETURN: break;
            case Keyword_Tokens::KEYWORD_INT: break;
            case Keyword_Tokens::KEYWORD_STRING: break;
            case Keyword_Tokens::KEYWORD_CHAR: break;
            case Keyword_Tokens::KEYWORD_FLOAT: break;
            case Keyword_Tokens::KEYWORD_DOUBLE: break;
            case Keyword_Tokens::KEYWORD_BOOL: break;
            case Keyword_Tokens::KEYWORD_TRUE: break;
            case Keyword_Tokens::KEYWORD_FALSE: break;
            case Keyword_Tokens::KEYWORD_FUNCTION: break;
            case Keyword_Tokens::KEYWORD_STRUCT: break;
            case Keyword_Tokens::KEYWORD_ENUM: break;
            case Keyword_Tokens::KEYWORD_IMPORT: break;
            case Keyword_Tokens::KEYWORD_MACRO: break;
            case Keyword_Tokens::KEYWORD_COMPILER: break;
            case Keyword_Tokens::KEYWORD_VOID: break;
            default:
                message(UNKNOWN_TOKEN, FL_compiler3, 
                "Unknown keyword subtype: " + 
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
            switch (tokens[cur_ind].subtype) {
            case Identifier_Tokens::IDENTIFIER_VARIABLE: break;
            case Identifier_Tokens::IDENTIFIER_FUNCTION: break;
            case Identifier_Tokens::IDENTIFIER_STRUCT: break;
            case Identifier_Tokens::IDENTIFIER_ENUM: break;
            case Identifier_Tokens::IDENTIFIER_MACRO: break;
            case Identifier_Tokens::IDENTIFIER_COMPILER: break;
            case Identifier_Tokens::IDENTIFIER_FUNC_CALL: break;
            case Identifier_Tokens::IDENTIFIER_VAR_DECL: break;
            case Identifier_Tokens::IDENTIFIER_VAR_ASSIGN: break;
            case Identifier_Tokens::IDENTIFIER_IMPORT: break;
            case Identifier_Tokens::IDENTIFIER_ARGUMENT: break;
            
            case Identifier_Tokens::IDENTIFIER_UNKNOWN: 
                message(UNKNOW_IDENTIFIER, FL_compiler3, 
                "Unknown identifier found '" +
                tokens[cur_ind].value +
                "' at line: " + 
                std::to_string(tokens[cur_ind].line) +
                " column: " +
                std::to_string(tokens[cur_ind].column), 
                true);
                break;
            default:
                message(UNKNOWN_TOKEN, FL_compiler3, 
                "Unknown identifier subtype: " + 
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
        default: 
            message(UNKNOWN_TOKEN, FL_compiler3,
            "Unknown token type: " +
            std::to_string(tokens[cur_ind].type) +
            + " value: " +
            tokens[cur_ind].value +
            " at line: " +
            std::to_string(tokens[cur_ind].line) +
            " column: " +
            std::to_string(tokens[cur_ind].column),
            true);
            break;
        }
    }

}


