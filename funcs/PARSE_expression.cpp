#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>
#include <iostream>

// 3. Parse expression

std::shared_ptr<Parse_Expression> parse_expression(std::vector<Token> &tokens, size_t& index) {
    std::vector<Parse_Term> terms;
    std::vector<char> ops;

    terms.push_back(*parse_term(tokens, index)); // parse the first term

    // while there are still operators, parse the next term
    while (index < tokens.size() && 
                (tokens[index].type == Tokens::OPERATOR && 
                    (tokens[index].subtype == Operator_Tokens::ADD ||
                    tokens[index].subtype == Operator_Tokens::SUB))) {
        ops.push_back(tokens[index].value[0]);          // store the operator
        index++;                                        // skip the operator             
        terms.push_back(*parse_term(tokens, index));    // parse the next term
    }

    return std::make_shared<Parse_Expression>(terms, ops);
}