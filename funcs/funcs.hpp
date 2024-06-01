#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../compiler.hpp"

struct Parsed_common_function {
    std::string name;
    std::vector<std::shared_ptr<Parse_Expression>> args;

    Parsed_common_function(std::string n, std::vector<std::shared_ptr<Parse_Expression>> a)
        : name(n), args(a) {}
};











std::shared_ptr<Parsed_common_function> parse_common_function(std::vector<Token> &tokens, size_t &cur_ind);
std::shared_ptr<Parse_Expression> parse_expression(std::vector<Token> &tokens, size_t& index);
std::shared_ptr<Parse_Factor> parse_factor(std::vector<Token> &tokens, size_t& index);
std::shared_ptr<Parse_Term> parse_term(std::vector<Token> &tokens, size_t& index);

