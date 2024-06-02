#pragma once
#include <string>
#include <vector>
#include <memory> // shared_ptr
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

/*+++
Tokenizer enums and structs
---*/
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

    /*
    TODO ADD:
    KEYWORD_BREAK
    KEYWORD_CONTINUE
    KEYWORD_SWITCH
    KEYWORD_CASE
    KEYWORD_DEFAULT
    KEYWORD_DO
    KEYWORD_GOTO
    KEYWORD_SIZEOF
    KEYWORD_TYPEOF
    KEYWORD_EXPORT
    */
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
    DEC,                    // --
    MUL_ASSIGN,             // *=
    DIV_ASSIGN,             // /=
    MOD_ASSIGN,             // %=
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
    BOOL_LITERAL,           // true, false
    VOID_LITERAL,           // void
    HEX_LITERAL,            // 0x1
};

// Identifier names are stored in the value field
// of the token struct.
// more accurate information will be gathered in syntaxanalysis
enum Identifier_Tokens {
    IDENTIFIER_VARIABLE,    // variable
    IDENTIFIER_FUNCTION,    // function
    IDENTIFIER_STRUCT,      // struct
    IDENTIFIER_ENUM,        // enum
    IDENTIFIER_MACRO,       // macro
    IDENTIFIER_COMPILER,    // compiler
    IDENTIFIER_UNKNOWN,     // unknown, i'll use this in lexanalysis. 
    //i can't know if it is a variable or a function before syntaxanalysis 
    IDENTIFIER_FUNC_CALL,   // function call
    IDENTIFIER_FUNC_DECL,   // function declaration
    IDENTIFIER_VAR_DECL,    // variable declaration
    IDENTIFIER_VAR_ASSIGN,  // variable assignment
    IDENTIFIER_IMPORT,      // include | import
    IDENTIFIER_ARGUMENT,    // argument
};

enum Comment_Tokens {
    LINE_COMMENT,           // //
    BLOCK_COMMENT           // /* */
};



/*+++
Preprocessor_Tokens is not used in the lexer -
since they are all keywords too and will be -
treated as such

enum Preprocessor_Tokens {
    PREPROCESSOR_IMPORT,    // #include
    PREPROCESSOR_MACRO,     // #define
    PREPROCESSOR_COMPILER   // #pragma
};
---*/

#define mcr_WHITESPACE_SPACE            0x20
#define mcr_WHITESPACE_TAB              0x09
#define mcr_WHITESPACE_NEWLINE          0x0A
#define mcr_WHITESPACE_RETURN           0x0D

enum Whitespace_Tokens {
    WHITESPACE_SPACE,       // ' '      0x20
    WHITESPACE_TAB,         // '\t'     0x09
    WHITESPACE_NEWLINE,     // '\n'     0x0A
    WHITESPACE_RETURN       // '\r'     0x0D. Should be ['0x0D', '0x0A']. But I'll treat it as 0x0D since switch case is easier
};

struct Token {
    Tokens type;
    int subtype;
    std::string value;
    int line;
    int column;
    Token(Tokens t, int st, std::string val, int l, int c) : type(t), subtype(st), value(val), line(l), column(c)
    {}
};

std::vector<Token>* lexanalysis(std::vector<std::string> &s_arguments);

void IDENTIFIER_UNKNOWN_fix(std::vector<Token> &tokens);

/*+++
Syntax analysis and parser struct and enums
---*/
void syntaxanalysis(std::vector<Token> &tokens);


enum class Expression_Types {
    Literal,
    Identifier, // Variable
    Operator, // Operator
    Expression, // Subexpression
    Term, // Term
    Factor // Factor
};
/*+++
Parser structs in order of appearance -
lowest to highest
Parse_Factor -> Parse_Term -> Parse_Expression
---*/

// Factor is the lowest level of the parser
// it is a number or a subexpression
struct Parse_Factor {
    Expression_Types type;
    std::string value;
    std::shared_ptr<struct Parse_Expression> subexpression; // Optional subexpression

    // Constructor for literals (numbers and strings)
    Parse_Factor(Expression_Types t, std::string val, std::shared_ptr<Parse_Expression> subexpr = nullptr) 
        : type(t), value(val), subexpression(subexpr) {}

    // Constructor for expressions
    Parse_Factor(Expression_Types t, std::shared_ptr<Parse_Expression> subexpr) 
        : type(t), value(""), subexpression(subexpr) {}
};


// Term is a collection of factors and operators
// it is a multiplication or division of factors
struct Parse_Term {
    std::vector<Parse_Factor> factors;
    std::vector<char> operators; // Operators between factors

    Parse_Term(const std::vector<Parse_Factor>& f, const std::vector<char>& ops) 
        : factors(f), operators(ops) {}
};

// Expression is a collection of terms and operators
// it is an addition or subtraction of terms
struct Parse_Expression {
    std::vector<Parse_Term> terms;
    std::vector<char> operators; // Operators between terms

    Parse_Expression(const std::vector<Parse_Term>& t, const std::vector<char>& ops) 
        : terms(t), operators(ops) {}
};

// Statement is a value and an expression
// it is a variable assignment or a function call
struct Parse_Statement {
    std::string value;
    std::shared_ptr<Parse_Expression> expression;
    Parse_Statement(std::string val, std::shared_ptr<Parse_Expression> exp) 
        : value(val), expression(exp) {}
};

// Function is a collection of statements
// it is a function definition
struct Parse_Function {
    std::string name;
    std::vector<Parse_Statement> statements;
    Parse_Function(std::string n, const std::vector<Parse_Statement>& s) 
        : name(n), statements(s) {}
};



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