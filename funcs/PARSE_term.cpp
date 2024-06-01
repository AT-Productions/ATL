#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>
#include <iostream>
// 2. Parse term

std::shared_ptr<Parse_Term> parse_term(std::vector<Token> &tokens, size_t& index) {
    std::vector<Parse_Factor> factors;
    std::vector<char> ops;

    factors.push_back(*parse_factor(tokens, index)); // parse the first factor

    // while there are still operators, parse the next factor
    while (index < tokens.size() && 
                (tokens[index].type == Tokens::OPERATOR && 
                    (tokens[index].subtype == Operator_Tokens::MUL ||
                    tokens[index].subtype == Operator_Tokens::DIV))) {
        ops.push_back(tokens[index].value[0]);              // store the operator
        index++;                                            // skip the operator             
        factors.push_back(*parse_factor(tokens, index));    // parse the next factor
    }

    return std::make_shared<Parse_Term>(factors, ops);
}