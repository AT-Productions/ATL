#pragma once
#include <string>
#include <vector>
#if defined(LINUX) || defined(__linux__)
#include <cstring>   // strcmp
#include <algorithm> // std::find_if
#endif

#define VERSION_MAJOR           0
#define VERSION_MINOR           1
#define VERSION_PATCH           0
#define VERSION_BUILD           1


#define OUTPUT                  0       // POSITION OF OUTPUT IN S_ARGUMENTS
#define INPUT                   1       // POSITION OF INPUT IN S_ARGUMENTS

#define S_ARG_SIZE              2       // SIZE OF S_ARGUMENTS
extern std::vector<std::string> s_arguments;

enum Tokens {
    KEYWORD,
    OPERATOR,
    SEPARATOR,
    LITERAL,
    IDENTIFIER,
    COMMENT,
    PREPROCESSOR,
    WHITESPACE,
};

enum Keyword_Tokens {
    KEYWORD_EXIT,           // exit
    KEYWORD_IF,             // if
    KEYWORD_ELSE,           // else
    KEYWORD_WHILE,          // while
    KEYWORD_FOR,            // for
    KEYWORD_RETURN,         // return
    KEYWORD_INT,            // int
    KEYWORD_STRING,         // string
    KEYWORD_CHAR,           // char
    KEYWORD_FLOAT,          // float
    KEYWORD_DOUBLE,         // double
    KEYWORD_BOOL,           // bool
    KEYWORD_TRUE,           // true
    KEYWORD_FALSE,          // false
    KEYWORD_FUNCTION,       // function
    KEYWORD_STRUCT,         // struct
    KEYWORD_ENUM,           // enum
    KEYWORD_IMPORT,         // include  | import
    KEYWORD_MACRO,          // define   | macro
    KEYWORD_COMPILER,       // compiler |pragma
    KEYWORD_VOID            // void
};

enum Operator_Tokens {
    ADD,                    // +
    SUB,                    // -
    MUL,                    // *
    DIV,                    // /
    ASSIGN,                 // =
    ADD_ASSIGN,             // +=
    SUB_ASSIGN,             // -=
    EQ,                     // ==
    NEQ,                    // !=
    GT,                     // >
    LT,                     // <
    GTE,                    // >=
    LTE,                    // <=
    AND,                    // &&
    OR,                     // ||
    NOT,                    // !
    BIT_AND,                // &
    BIT_OR,                 // |
    BIT_XOR,                // ^
    BIT_NOT,                // ~
    LSHIFT,                 // <<
    RSHIFT,                 // >>
    MOD,                    // %
    INC,                    // ++
    DEC                     // --
};

enum Separator_Tokens {
    SEMICOLON,              // ;
    LBRACE,                 // {
    RBRACE,                 // }
    LPAREN,                 // (
    RPAREN,                 // )
    LBRACKET,               // [
    RBRACKET,               // ]
    COMMA,                  // ,
    DOT,                    // .
    COLON,                  // :
};

enum Literal_Tokens {
    INT_LITERAL,            // 1
    FLOAT_LITERAL,          // 1.0
    STRING_LITERAL,         // "string"
    CHAR_LITERAL,           // 'c'
    BOOL_LITERAL            // true, false
};

enum Identifier_Tokens {
    IDENTIFIER_VARIABLE,    // variable
    IDENTIFIER_FUNCTION,    // function
    IDENTIFIER_STRUCT,      // struct
    IDENTIFIER_ENUM,        // enum
    IDENTIFIER_MACRO,       // macro
    IDENTIFIER_COMPILER,    // compiler
    IDENTIFIER_UNKNOWN      // unknown, i'll use this in lexanalysis. 
    //i can't know if it is a variable or a function before syntaxanalysis 
};

enum Comment_Tokens {
    LINE_COMMENT,           // //
    BLOCK_COMMENT           // /* */
};

enum Preprocessor_Tokens {
    PREPROCESSOR_IMPORT,    // #include
    PREPROCESSOR_MACRO,     // #define
    PREPROCESSOR_COMPILER   // #pragma
};

enum Whitespace_Tokens {
    WHITESPACE_SPACE,       // ' '    0x20
    WHITESPACE_TAB,         // '\t'   0x09
    WHITESPACE_NEWLINE,     // '\n'   0x0A
    WHITESPACE_RETURN       // '\r'   0x0D
};

struct Token {
    Tokens type;
    int subtype;
    std::string value;
    Token(Tokens t, int st, std::string val) : type(t), subtype(st), value(val) {}
};

std::vector<Token>* lexanalysis(std::vector<std::string> &s_arguments);
void syntaxanalysis(std::vector<Token> &tokens);




// thanks to https://stackoverflow.com/a/217605
// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}