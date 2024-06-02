#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>

std::shared_ptr<Parsed_Token> parse_common_function(std::vector<Token> &tokens, size_t& index) {
    std::string function_name = tokens[index].value;
    std::vector<std::shared_ptr<Parse_Expression>> arguments;
    index++; // skip function name

    auto expr = parse_expression(tokens, index);
    arguments.push_back(expr);
    auto token = std::make_shared<Parsed_Token>(
        function_name, 
        "", 
        Parse_Types::PARSE_FUNCTION, 
        std::vector<std::shared_ptr<Parsed_Token>>(),
        arguments);
    return token;
}