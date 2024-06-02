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
    for(size_t i = 0; i < tokens.size(); i++){
        std::cout << "Type: '" << tokens[i].type << "' Subtype: '" << tokens[i].subtype << "' Value: '" << tokens[i].value << "'" << std::endl;
    }


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
        case Tokens::OPERATOR: 
            std::cout << "Operator: " << tokens[cur_ind].value << std::endl;
            switch (tokens[cur_ind].subtype){
            case Operator_Tokens::ADD: break;
            case Operator_Tokens::SUB: break;
            case Operator_Tokens::MUL: break;
            case Operator_Tokens::ASSIGN: break;
            case Operator_Tokens::ADD_ASSIGN: break;
            case Operator_Tokens::SUB_ASSIGN: break;
            case Operator_Tokens::EQ: break;
            case Operator_Tokens::NEQ: break;
            case Operator_Tokens::GT: break;
            case Operator_Tokens::LT: break;
            case Operator_Tokens::GTE: break;
            case Operator_Tokens::LTE: break;
            case Operator_Tokens::AND: break;
            case Operator_Tokens::OR: break;
            case Operator_Tokens::NOT: break;
            case Operator_Tokens::BIT_AND: break;
            case Operator_Tokens::BIT_OR: break;
            case Operator_Tokens::BIT_XOR: break;
            case Operator_Tokens::BIT_NOT: break;
            case Operator_Tokens::LSHIFT: break;
            case Operator_Tokens::RSHIFT: break;
            case Operator_Tokens::MOD: break;
            case Operator_Tokens::INC: break;
            case Operator_Tokens::DEC: break;
            default:
                message(UNKNOWN_TOKEN, FL_compiler3, 
                "Unknown operator subtype: " + 
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
        case Tokens::SEPARATOR: 
            std::cout << "Separator: " << tokens[cur_ind].value << std::endl;
            switch (tokens[cur_ind].subtype){
                case Separator_Tokens::SEMICOLON: break;
                case Separator_Tokens::LBRACE: break;
                case Separator_Tokens::RBRACE: break;
                case Separator_Tokens::LPAREN: break;
                case Separator_Tokens::RPAREN: break;
                case Separator_Tokens::LBRACKET: break;
                case Separator_Tokens::RBRACKET: break;
                case Separator_Tokens::COMMA: break;
                case Separator_Tokens::DOT: break;
                case Separator_Tokens::COLON: break;
                default:
                    message(UNKNOWN_TOKEN, FL_compiler3, 
                    "Unknown separator subtype: " + 
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
        case Tokens::LITERAL: 
            std::cout << "Literal: " << tokens[cur_ind].value << std::endl;
            switch (tokens[cur_ind].subtype){
            case Literal_Tokens::INT_LITERAL: break;
            case Literal_Tokens::FLOAT_LITERAL: break;
            case Literal_Tokens::STRING_LITERAL: break;
            case Literal_Tokens::CHAR_LITERAL: break;
            case Literal_Tokens::BOOL_LITERAL: break;
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
            switch (tokens[cur_ind].subtype){
                case Identifier_Tokens::IDENTIFIER_VARIABLE: break;
                case Identifier_Tokens::IDENTIFIER_FUNCTION: break;
                case Identifier_Tokens::IDENTIFIER_STRUCT: break;
                case Identifier_Tokens::IDENTIFIER_ENUM: break;
                case Identifier_Tokens::IDENTIFIER_MACRO: break;
                case Identifier_Tokens::IDENTIFIER_COMPILER: break;
                case Identifier_Tokens::IDENTIFIER_UNKNOWN: break;
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
        case Tokens::COMMENT: 
            std::cout << "Comment: " << tokens[cur_ind].value << std::endl;
            // No handling needed for comments for now
            break;
        // case Tokens::PREPROCESSOR: 
        //     std::cout << "Preprocessor: " << tokens[cur_ind].value << std::endl;
        //     // No handling needed for preprocessor for now
        //     break;
        case Tokens::WHITESPACE: 
            std::cout << "Whitespace: " << tokens[cur_ind].value << std::endl;
            switch (tokens[cur_ind].subtype){
                case Whitespace_Tokens::WHITESPACE_SPACE: break;
                case Whitespace_Tokens::WHITESPACE_TAB: break;
                case Whitespace_Tokens::WHITESPACE_NEWLINE: break;
                case Whitespace_Tokens::WHITESPACE_RETURN: break;
                default:
                    message(UNKNOWN_TOKEN, FL_compiler3, 
                    "Unknown whitespace subtype: " + 
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

    // Print the parse tree
    for (const auto& node : parsetree) {
        print_parsed_tree(node, 0);
    }
}


