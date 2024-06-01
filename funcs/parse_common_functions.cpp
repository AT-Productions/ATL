#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>

std::shared_ptr<Parsed_common_function> parse_common_function(std::vector<Token> &tokens, size_t& index) {
    std::string function_name = tokens[index].value;
    std::vector<std::shared_ptr<Parse_Expression>> arguments;
    index++; // skip function name

    auto expr = parse_expression(tokens, index);
    arguments.push_back(expr);

    return std::make_shared<Parsed_common_function>(function_name, arguments);
}