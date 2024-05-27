#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>



#define LOOK_FOR_WORDS 0
// list of keywords from compiler.hpp/Keyword_Tokens
std::string look_for_words[] = {
    "exit", "if", "else", "while", "for",
    "return", "int", "string", "char", "float",
    "double", "bool", "true", "false", "function",
    "struct", "enum", "define", "macro", "compiler"
};

#define LOOK_FOR_OPERATORS 1
// list of operators from compiler.hpp/Operator_Tokens
std::string look_for_operators[] = {
    "+", "-", "*", "/", "=", "+=", "-=",
    "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^",
    "~", "<<", ">>", "%", "++", "--"
};

#define LOOK_FOR_SEPARATORS 2
// list of separators from compiler.hpp/Separator_Tokens
std::string look_for_separators[] = {
    "(", ")", "{", "}", "[", "]", ";", ",", ".", ":"
};

#define LOOK_FOR_PREPROCESSOR 3
// list of preprocessor from compiler.hpp/Preprocessor_Tokens
std::string look_for_preprocessor[] = {
    "import", "macro", "compiler"
};

#define LOOK_FOR_LITERALS 4
// list of literals from compiler.hpp/Literal_Tokens
std::string look_for_literals[] = {
    "int", "string", "char", "float", "double", "bool"
};

int if_arr_contains(int array_type, std::string &buffer){
    int i = 0;
    switch (array_type){
    case LOOK_FOR_WORDS:
        for (const auto &word : look_for_words){
            if(word == buffer)
                return i;
            i++;
        }
        break;
    case LOOK_FOR_OPERATORS:
        for (const auto &op : look_for_operators){
            if(op == buffer)
                return i;
            i++;
        }
        break;
    case LOOK_FOR_SEPARATORS:
        for (const auto &sep : look_for_separators){
            if(sep == buffer)
                return i;
            i++;
        }
        break;
    case LOOK_FOR_PREPROCESSOR:
        for (const auto &pre : look_for_preprocessor){
            if(pre == buffer)
                return i;
            i++;
        }
        break;
    case LOOK_FOR_LITERALS:
        for (const auto &lit : look_for_literals){
            if(lit == buffer)
                return i;
            i++;
        }
        break;
    }
    return -1;
}

std::string look_ahead(uint16_t &cur_ind, std::string &line);

/*+++
this will simply check for the following exit< (1+2) > and add the tokens to the vector
---*/
void check_for_separators_args(std::vector<Token> *tokens, std::string &buffer, std::string &line, uint16_t &cur_ind) {
    std::string buf = "";
    for(uint16_t i = cur_ind; i < line.length(); i++){
        buf += line[i];
        switch (line[i]) {
        case '(':
            tokens->push_back(Token(SEPARATOR, LPAREN, "("));
            break;
        case ')':
            tokens->push_back(Token(SEPARATOR, RPAREN, ")"));
            break;
        case '{':
            tokens->push_back(Token(SEPARATOR, LBRACE, "{"));
            break;
        case '}':
            tokens->push_back(Token(SEPARATOR, RBRACE, "}"));
            break;
        case '[':
            tokens->push_back(Token(SEPARATOR, LBRACKET, "["));
            break;
        case ']':
            tokens->push_back(Token(SEPARATOR, RBRACKET, "]"));
            break;
        }
    }
    buffer = "";
}

std::vector<Token>* lexanalysis(std::vector<std::string> &s_arguments) {
    // Read file line by line, char by char
    std::ifstream file(s_arguments[INPUT], std::ios::binary);
    if (!file.is_open()) {
        message(ERR_OPEN_FILE, FL_compiler2, s_arguments[INPUT]);
        exit(ERR_OPEN_FILE);
    }

    std::string line;
    std::vector<Token> *tokens = new std::vector<Token>();
    std::string buffer;
    int line_num = 0;

    bool in_block_comment = false; // /* */
    bool in_line_comment = false; // //
    bool in_string = false; // ""
    bool in_char = false; // ''
    bool expect_pass = false;
    
    while (std::getline(file, line)) {
        line_num++;
        for(uint16_t cur_ind = 0; cur_ind < line.length(); cur_ind++){
            buffer += line[cur_ind];
            ltrim(buffer); // remove leading whitespace, don't see any issues for now :))))))))
            if(!in_string){
                std::string look_next = look_ahead(cur_ind, line);
                
                cur_ind--; // bad logic, will fix later
                switch(line[cur_ind]){
                    case '/':
                        if(look_ahead(cur_ind, line) == "/"){
                            for(uint16_t i = cur_ind; i < line.length(); i++){
                                buffer += line[i];
                                if(line[i] == '\\'){ //comment extends to next line
                                    std::string next = look_ahead(cur_ind, line);
                                    if(next == "\n" || next == "\r\n"){
    // #pragma message("TODO FIX or add multiple line comment logic (singleline comment is working, use of \\ to extend comment to next line is not working yet)")
                                        in_line_comment = true;
                                        break;
                                    }
                                }
                            }
                            tokens->push_back(Token(COMMENT, LINE_COMMENT, buffer));
                        }
                        else if(look_ahead(cur_ind, line) == "*"){
                            in_block_comment = true;
                        }
                        break;
                }
                int check_separators = if_arr_contains(LOOK_FOR_SEPARATORS, buffer);
                if(check_separators != -1){
                    switch (check_separators)
                    {
                    case 0: tokens->push_back(Token(SEPARATOR, LPAREN, buffer)); break;
                    case 1: tokens->push_back(Token(SEPARATOR, RPAREN, buffer)); break;
                    case 2: tokens->push_back(Token(SEPARATOR, LBRACE, buffer)); break;
                    case 3: tokens->push_back(Token(SEPARATOR, RBRACE, buffer)); break;
                    case 4: tokens->push_back(Token(SEPARATOR, LBRACKET, buffer)); break;
                    case 5: tokens->push_back(Token(SEPARATOR, RBRACKET, buffer)); break;
                    case 6: tokens->push_back(Token(SEPARATOR, SEMICOLON, buffer)); break;
                    case 7: tokens->push_back(Token(SEPARATOR, COMMA, buffer)); break;
                    case 8: tokens->push_back(Token(SEPARATOR, DOT, buffer)); break;
                    default: message(SYNTAX, FL_compiler2, buffer); exit(SYNTAX);
                    }
                    buffer = "";
                    continue;
                }
                int check_operators = if_arr_contains(LOOK_FOR_OPERATORS, buffer);
                if(check_operators != -1){
                    switch (check_operators){
                    case 1: tokens->push_back(Token(OPERATOR, ADD, buffer)); break;
                    case 2: tokens->push_back(Token(OPERATOR, SUB, buffer)); break;
                    case 3: tokens->push_back(Token(OPERATOR, MUL, buffer)); break;
                    case 4: tokens->push_back(Token(OPERATOR, DIV, buffer)); break;
                    case 5: tokens->push_back(Token(OPERATOR, ASSIGN, buffer)); break;
                    case 6: tokens->push_back(Token(OPERATOR, ADD_ASSIGN, buffer)); break;
                    case 7: tokens->push_back(Token(OPERATOR, SUB_ASSIGN, buffer)); break;
                    case 8: tokens->push_back(Token(OPERATOR, EQ, buffer)); break;
                    case 9: tokens->push_back(Token(OPERATOR, NEQ, buffer)); break;
                    case 10: tokens->push_back(Token(OPERATOR, GT, buffer)); break;
                    case 11: tokens->push_back(Token(OPERATOR, LT, buffer)); break;
                    case 12: tokens->push_back(Token(OPERATOR, GTE, buffer)); break;
                    case 13: tokens->push_back(Token(OPERATOR, LTE, buffer)); break;
                    case 14: tokens->push_back(Token(OPERATOR, AND, buffer)); break;
                    case 15: tokens->push_back(Token(OPERATOR, OR, buffer)); break;
                    case 16: tokens->push_back(Token(OPERATOR, NOT, buffer)); break;
                    case 17: tokens->push_back(Token(OPERATOR, BIT_AND, buffer)); break;
                    case 18: tokens->push_back(Token(OPERATOR, BIT_OR, buffer)); break;
                    case 19: tokens->push_back(Token(OPERATOR, BIT_XOR, buffer)); break;
                    case 20: tokens->push_back(Token(OPERATOR, BIT_NOT, buffer)); break;
                    case 21: tokens->push_back(Token(OPERATOR, LSHIFT, buffer)); break;
                    case 22: tokens->push_back(Token(OPERATOR, RSHIFT, buffer)); break;
                    case 23: tokens->push_back(Token(OPERATOR, MOD, buffer)); break;
                    case 24: tokens->push_back(Token(OPERATOR, INC, buffer)); break;
                    case 25: tokens->push_back(Token(OPERATOR, DEC, buffer)); break;
                    default: message(SYNTAX, FL_compiler2, buffer); exit(SYNTAX);
                    }
                    buffer = "";
                    continue;
                }
                int check_words = if_arr_contains(LOOK_FOR_WORDS, buffer);
                if(check_words != -1) {
                    // will improve this later
                    switch (check_words){
                    case 0: tokens->push_back(Token(KEYWORD, KEYWORD_EXIT, buffer)); break;
                    case 1: tokens->push_back(Token(KEYWORD, KEYWORD_IF, buffer)); break;
                    case 2: tokens->push_back(Token(KEYWORD, KEYWORD_ELSE, buffer)); break;
                    case 3: tokens->push_back(Token(KEYWORD, KEYWORD_WHILE, buffer)); break;
                    case 4: tokens->push_back(Token(KEYWORD, KEYWORD_FOR, buffer)); break;
                    case 5: tokens->push_back(Token(KEYWORD, KEYWORD_RETURN, buffer)); break;
                    case 6: tokens->push_back(Token(KEYWORD, KEYWORD_INT, buffer)); break;
                    case 7: tokens->push_back(Token(KEYWORD, KEYWORD_STRING, buffer)); break;
                    case 8: tokens->push_back(Token(KEYWORD, KEYWORD_CHAR, buffer)); break;
                    case 9: tokens->push_back(Token(KEYWORD, KEYWORD_FLOAT, buffer)); break;
                    case 10: tokens->push_back(Token(KEYWORD, KEYWORD_DOUBLE, buffer)); break;
                    case 11: tokens->push_back(Token(KEYWORD, KEYWORD_BOOL, buffer)); break;
                    case 12: tokens->push_back(Token(KEYWORD, KEYWORD_TRUE, buffer)); break;
                    case 13: tokens->push_back(Token(KEYWORD, KEYWORD_FALSE, buffer)); break;
                    case 14: tokens->push_back(Token(KEYWORD, KEYWORD_FUNCTION, buffer)); break;
                    case 15: tokens->push_back(Token(KEYWORD, KEYWORD_STRUCT, buffer)); break;
                    case 16: tokens->push_back(Token(KEYWORD, KEYWORD_ENUM, buffer)); break;
                    case 17: tokens->push_back(Token(KEYWORD, KEYWORD_IMPORT, buffer)); break;
                    case 18: tokens->push_back(Token(KEYWORD, KEYWORD_MACRO, buffer)); break;
                    case 19: tokens->push_back(Token(KEYWORD, KEYWORD_COMPILER, buffer)); break;
                    default: message(SYNTAX, FL_compiler2, buffer); exit(SYNTAX);
                    }
                    buffer = "";
                    continue;
                }
                int check_preprocessor = if_arr_contains(LOOK_FOR_PREPROCESSOR, buffer);
                if(check_preprocessor != -1){
                    switch (check_preprocessor){
                    case 0: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_IMPORT, buffer)); break;
                    case 1: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_MACRO, buffer)); break;
                    case 2: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_COMPILER, buffer)); break;
                    default: message(SYNTAX, FL_compiler2, buffer); exit(SYNTAX);
                    }
                    buffer = "";
                    continue;
                }
                
                /*+++
                floats and doubles (such as 12.1) will be tokenized as:
                ================================================================
                Type: 3 Subtype: 0 Value: 12    ||    LITERAL,  INT_LITERAL, 12
                Type: 2 Subtype: 8 Value: .     ||    OPERATOR, DOT        , .
                Type: 3 Subtype: 0 Value: 1     ||    LITERAL,  INT_LITERAL, 1
                ================================================================
                which will be later converted to 12.1 in the syntax analysis
                ---*/
                if(std::isdigit(line[cur_ind])){
                    while(std::isdigit(look_ahead(cur_ind, line)[0])){
                        buffer += line[cur_ind];
                    }
                    // TODO test this decriment
                    cur_ind--;
                    tokens->push_back(Token(LITERAL, INT_LITERAL, buffer));
                    buffer = "";
                    continue;
                }

                look_next = look_ahead(cur_ind, line);
                cur_ind--; // bad logic, will fix later
                if(look_next == " " || look_next == "\n" || look_next == "\r\n"){
                    // IDENTIFIER_UNKNOWN is a placeholder for now, explained in compiler.hpp
                    tokens->push_back(Token(IDENTIFIER, IDENTIFIER_UNKNOWN, buffer));
                    buffer = "";
                    continue;
                }

            }
        }


        buffer = "";
    }
    file.close();

    return tokens;
}

std::string look_ahead(uint16_t &cur_ind, std::string &line) {
    cur_ind++;
    if(cur_ind >= line.length())
        return "";
    else
        return line.substr(cur_ind, 1);
}