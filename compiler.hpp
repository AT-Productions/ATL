#pragma once
#include <string>
#include <vector>

#define VERSION_MAJOR           0
#define VERSION_MINOR           1
#define VERSION_PATCH           0
#define VERSION_BUILD           1


#define OUTPUT                  0       // POSITION OF OUTPUT IN S_ARGUMENTS
#define INPUT                   1       // POSITION OF INPUT IN S_ARGUMENTS

#define S_ARG_SIZE              2       // SIZE OF S_ARGUMENTS
extern std::vector<std::string> s_arguments;

void Parser(std::vector<std::string> &s_arguments);


enum Tokens {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    SEPARATOR,
    LITERAL,
    COMMENT,
    PREPROCESSOR
};

enum Keywords {
    EXIT,
};

struct Token {
    Tokens type;
    std::string value;
};