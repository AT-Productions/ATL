#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../compiler.hpp"
#include <optional>

/*+++
I don't what i am doing
---*/
enum class Parse_Types {
    PARSE_EXPRESSION,
    PARSE_TERM,
    PARSE_FACTOR,
    PARSE_COMMON_FUNCTION,
    PARSE_FUNCTION,
    PARSE_STATEMENT,
    PARSE_DECLARATION,
    PARSE_ASSIGNMENT,
    PARSE_RETURN,
    PARSE_IF,
    PARSE_WHILE,
    PARSE_FOR,
    PARSE_STRUCT,
    PARSE_ENUM,
    PARSE_IMPORT,
    PARSE_MACRO,
    PARSE_COMPILER,
    PARSE_VOID,
    PARSE_INT,
    PARSE_STRING,
    PARSE_CHAR,
    PARSE_FLOAT,
    PARSE_DOUBLE,
    PARSE_BOOL,
    PARSE_TRUE,
    PARSE_FALSE,
    PARSE_IDENTIFIER,
    PARSE_LITERAL,
    PARSE_OPERATOR,
    PARSE_SEPARATOR,
    PARSE_KEYWORD,
    PARSE_COMMENT,
    PARSE_PREPROCESSOR,
    PARSE_WHITESPACE,
};

struct Parsed_Token {
    std::string name;  // name of the token
    std::string value;  // value of the token
    std::vector<std::shared_ptr<Parsed_Token>> children;  // children of the token
    std::optional<std::vector<std::shared_ptr<Parse_Expression>>> args;  // arguments of the token
    Parse_Types type;  // type of the token

    // Constructor for a token with value and type
    // Used for tokens that don't have children, like variables, literals, etc.
    Parsed_Token(std::string n, std::string v, Parse_Types t)
        : name(n), value(v), type(t) {}

    // Constructor for a token with value, type, and children
    // Used for tokens that have children, like expressions, statements, etc.
    Parsed_Token(std::string n, std::string v, Parse_Types t, std::vector<std::shared_ptr<Parsed_Token>> c)
        : name(n), value(v), type(t), children(c) {}

    // Constructor for a token with value, type, children, and arguments
    // Used for tokens that have children and arguments, like functions, declarations, etc.
    Parsed_Token(std::string n, std::string v, Parse_Types t, std::vector<std::shared_ptr<Parsed_Token>> c, std::vector<std::shared_ptr<Parse_Expression>> a)
        : name(n), value(v), type(t), children(c), args(a) {}

    // Add a child to this token
    void add_child(std::shared_ptr<Parsed_Token> child) {
        children.push_back(child);
    }

    // Add an argument to this token
    void add_arg(std::shared_ptr<Parse_Expression> arg) {
        if (!args) {
            args = std::vector<std::shared_ptr<Parse_Expression>>();
        }
        args->push_back(arg);
    }
};


std::shared_ptr<Parsed_Token> parse_common_function(std::vector<Token> &tokens, size_t &cur_ind);

std::shared_ptr<Parse_Expression> parse_expression(std::vector<Token> &tokens, size_t& index);
std::shared_ptr<Parse_Factor> parse_factor(std::vector<Token> &tokens, size_t& index);
std::shared_ptr<Parse_Term> parse_term(std::vector<Token> &tokens, size_t& index);

void print_parsed_tree(const std::shared_ptr<Parsed_Token>& node, int depth);