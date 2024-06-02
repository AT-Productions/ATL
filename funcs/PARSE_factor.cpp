#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>
#include "../glb/message.hpp"
#include <iostream>
// 1. Parse factor

std::shared_ptr<Parse_Factor> parse_factor(std::vector<Token> &tokens, size_t& index) {
    std::cout << "String or char literal: " << tokens[index].value << std::endl;
    if (tokens[index].type == Tokens::LITERAL && 
        (tokens[index].subtype == Literal_Tokens::INT_LITERAL ||
        tokens[index].subtype == Literal_Tokens::FLOAT_LITERAL))
    {
        return std::make_shared<Parse_Factor>(Expression_Types::Literal, tokens[index++].value);
    } 
    else if(tokens[index].type == Tokens::LITERAL && (
        tokens[index].subtype == Literal_Tokens::STRING_LITERAL ||
        tokens[index].subtype == Literal_Tokens::CHAR_LITERAL
    )) {
        return std::make_shared<Parse_Factor>(Expression_Types::Literal, tokens[index++].value);
    } 
    else if (tokens[index].type == Tokens::SEPARATOR && 
               tokens[index].subtype == Separator_Tokens::LPAREN) {
        index++; // skip '(' 
        auto expr = parse_expression(tokens, index);
        index++; // skip ')'
        return std::make_shared<Parse_Factor>(Expression_Types::Expression, expr);
    } else {
        message(
            INVALID_ARGUMENT_PARSER,
            FL_parse_term,
            "Invalid argument in factor parser. Expected a literal or an identifier, got: '" + tokens[index].value + 
            "' from line: " + std::to_string(tokens[index].line) + " column: " + std::to_string(tokens[index].column)
            + " of type: " + std::to_string(tokens[index].type) + " and subtype: " + std::to_string(tokens[index].subtype)
            ,
            true
        );
        return nullptr;
    }
}
