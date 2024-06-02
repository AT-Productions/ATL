#include "compiler.hpp"
#include "glb/message.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>



#define LOOK_FOR_WORDS          0
// list of keywords from compiler.hpp/Keyword_Tokens
std::string look_for_words[] = {
    "exit", "if", "else", "while", "for",
    "return", "int", "string", "char", "float",
    "double", "bool", "true", "false", "function",
    "struct", "enum", "define", "macro", "compiler",
    "void"
};

#define LOOK_FOR_OPERATORS      1
// list of operators from compiler.hpp/Operator_Tokens
std::string look_for_operators[] = {
    "+", "-", "*", "/", "=", "+=", "-=",
    "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^",
    "~", "<<", ">>", "%", "++", "--",
    "*=", "/=", "%=" // TODO TEST
};

#define LOOK_FOR_SEPARATORS     2
// list of separators from compiler.hpp/Separator_Tokens
std::string look_for_separators[] = {
    "(", ")", "{", "}", "[", "]", ";", ",", ".", ":"
};

// Don't think these are needed for now
// #define LOOK_FOR_PREPROCESSOR    3
// list of preprocessor from compiler.hpp/Preprocessor_Tokens
// std::string look_for_preprocessor[] = {
//     "import", "macro", "compiler"
// };

#define LOOK_FOR_LITERALS       4
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
    // case LOOK_FOR_PREPROCESSOR:
    //     for (const auto &pre : look_for_preprocessor){
    //         if(pre == buffer)
    //             return i;
    //         i++;
    //     }
    //     break;
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

std::string look_ahead(size_t &cur_ind, std::string &line);
void check_separators(int x, std::vector<Token> *tokens, std::string &buffer);
void check_operators(int x, std::vector<Token> *tokens, std::string &buffer);
void check_keywords(int x, std::vector<Token> *tokens, std::string &buffer);
// void check_preprocessor(int x, std::vector<Token> *tokens, std::string &buffer);
int line_num = 0;
int line_pos = 0;

std::vector<Token>* lexanalysis(std::vector<std::string> &s_arguments) {
    line_num = 0;
    line_pos = 1;
    // Read file line by line, char by char
    std::ifstream file(s_arguments[INPUT], std::ios::binary);
    if (!file.is_open()) {
        message(ERR_OPEN_FILE, FL_compiler2, s_arguments[INPUT], true);
    }

    std::string line;
    std::vector<Token> *tokens = new std::vector<Token>();
    std::string buffer;

    bool in_block_comment = false;
    bool in_line_comment = false;
    bool expect_pass = false;
    char prev_char = '\0';
    char curr_char = '\0';
    char next_char = '\0';
    int i_free_use = 0;
    std::string test;
    while (std::getline(file, line)) {
        line_num++;
        for(size_t cur_ind = 0; cur_ind <= line.length(); cur_ind++){
            line_pos++;
            buffer += line[cur_ind];
            ltrim(buffer); // remove leading whitespace, don't see any issues for now :))))))))
            // EXPERIMENTAL
            // trim(buffer); // remove leading and trailing whitespace
            if(in_block_comment){
                if(buffer[buffer.length()-2] == '*' && buffer[buffer.length()-1] == '/'){
                    in_block_comment = false;
                    tokens->push_back(Token(COMMENT, BLOCK_COMMENT, buffer, line_num, line_pos));
                    buffer = "";
                }
                continue;
            }
            switch (line[cur_ind]){
                case '/':
                    next_char = look_ahead(cur_ind, line)[0];
                    cur_ind--;
                    if(next_char == '/'){
                        // buffer += '/';
                        while(true){
                            buffer += look_ahead(cur_ind, line)[0];
                            if(line.length() < cur_ind){
                                break;
                            }
                        }
                        tokens->push_back(Token(COMMENT, LINE_COMMENT, buffer, line_num, line_pos));
                        buffer = "";
                        break;
                    } 
                    else if (next_char == '*'){
                        // Start of block comment
                        // buffer += '*';
                        in_block_comment = true;
                        break;
                    }
                    else {
                        // is not good, will fix later
                        if(next_char == '='){
                            buffer += '=';
                            tokens->push_back(Token(OPERATOR, DIV_ASSIGN, buffer, line_num, line_pos));
                            buffer = "";
                            cur_ind++;
                            continue;
                        } else {
                            // must check for division operator. can be optimized. not feeling like it now
                            int i_check_operators = if_arr_contains(LOOK_FOR_OPERATORS, buffer);
                            if(i_check_operators != -1){
                                check_operators(i_check_operators, tokens, buffer);
                                buffer = "";
                                continue;
                            }
                        }
                    }
                    break;
                case mcr_WHITESPACE_NEWLINE:
                    tokens->push_back(Token(WHITESPACE, WHITESPACE_NEWLINE, "\n", line_num, line_pos));
                    break;
                case mcr_WHITESPACE_RETURN:
                    tokens->push_back(Token(WHITESPACE, WHITESPACE_RETURN, "\r", line_num, line_pos));
                    break;
                case '"': 
                    // string
                    // might do a better version of this later with logic in while loop
                    i_free_use = 0;
                    prev_char = '\0';
                    curr_char = '\0';
                    while(true){
                        curr_char = look_ahead(cur_ind, line)[0];
                        if(i_free_use > 0 && curr_char == '"' && prev_char != '\\'
                            || line.length() < cur_ind
                        ){
                            break;
                        }
                        buffer += line[cur_ind];
                        prev_char = line[cur_ind];
                        i_free_use++;
                    }
                    if(curr_char == '"'){
                        buffer += '"';
                        tokens->push_back(Token(LITERAL, STRING_LITERAL, buffer, line_num, line_pos));
                        cur_ind++;
                    } else {
                        message(TOKENIZER_SYNTAX, FL_compiler2, "String not closed at row: " + std::to_string(line_num) + " @ " + std::to_string(line_pos) + " - " + buffer, true);
                    }
                    buffer = "";

                    /*+++
                    reason for decrement:
                    print('"')
                    without:
Type: 2 Subtype: 3 Value: print
Type: 2 Subtype: 3 Value: (
Type: 3 Subtype: 3 Value: '"'
Missing the closing quote
                    with:
Type: 2 Subtype: 3 Value: print
Type: 2 Subtype: 3 Value: (
Type: 3 Subtype: 3 Value: '"'
Type: 2 Subtype: 4 Value: )

                    ~might~ cause problems later
                    same for char
                    ---*/
                    cur_ind--;
                    continue;
                case '\'': // char
                    i_free_use = 0;
                    prev_char = '\0';
                    while(true){
                        curr_char = look_ahead(cur_ind, line)[0];
                        if(i_free_use > 0 && curr_char == '\'' && prev_char != '\\'
                            || line.length() < cur_ind
                        ){
                            break;
                        }
                        buffer += line[cur_ind];
                        prev_char = line[cur_ind];
                        i_free_use++;
                    }
                    if(curr_char == '\''){
                        buffer += '\'';
                        tokens->push_back(Token(LITERAL, CHAR_LITERAL, buffer, line_num, line_pos));
                        cur_ind++;
                    } else {
                        message(TOKENIZER_SYNTAX, FL_compiler2, "Char not closed at row: " + std::to_string(line_num) + " @ " + std::to_string(line_pos) + " - " + buffer, true);
                    }
                    buffer = "";
                    cur_ind--;
                    continue;
            default: // other
                std::string look_next = look_ahead(cur_ind, line);
                cur_ind--; // bad logic, will fix later

                int i_check_separators = if_arr_contains(LOOK_FOR_SEPARATORS, buffer);
                if(i_check_separators != -1){
                    check_separators(i_check_separators, tokens, buffer);
                    buffer = "";
                    continue;
                }

                int i_check_operators = if_arr_contains(LOOK_FOR_OPERATORS, buffer);
                if(i_check_operators != -1){
                    /*+++
                    Since double length operators exist (++, <<, ||)
                    I have to check for the next character to see if it is an operator
                    propably a better way to do this, will fix later
                    :-)
                    ---*/
                    int i_check_operators_next = if_arr_contains(LOOK_FOR_OPERATORS, look_next);
                    if(i_check_operators_next != -1){
                        buffer += look_next;
                        cur_ind++; // since we are looking ahead

                        // check for double length operators
                        i_check_operators = if_arr_contains(LOOK_FOR_OPERATORS, buffer);
                    }
                    check_operators(i_check_operators, tokens, buffer);
                    buffer = "";
                    continue;
                }
                
                int i_check_words = if_arr_contains(LOOK_FOR_WORDS, buffer);
                // check for keywords
                // 0x20 is space, 0x0A is newline, 0x0D is carriage return, 0x09 is tab
                if(i_check_words != -1)
                {
                    check_keywords(i_check_words, tokens, buffer);
                    buffer = "";
                    continue;
                }
                // int i_check_preprocessor = if_arr_contains(LOOK_FOR_PREPROCESSOR, buffer);
                // if(i_check_preprocessor != -1 && (look_next[0] == 0x0A || look_next[0] == 0x0D || look_next[0] == 0x09)){
                //     check_preprocessor(i_check_preprocessor, tokens, buffer);
                //     buffer = "";
                //     continue;
                // }
                
                if(std::isdigit(line[cur_ind]) && buffer.size() == 1 && std::isdigit(buffer[0])){
                    curr_char = '\0';
                    while(std::isdigit(curr_char = look_ahead(cur_ind, line)[0]) || curr_char== '.'){
                        buffer += line[cur_ind];
                    }
                    // TODO test this decriment
                    // -- propably works
                    cur_ind--;
                    if(buffer.find('.') == std::string::npos){
                        tokens->push_back(Token(LITERAL, INT_LITERAL, buffer, line_num, line_pos));
                    } else {
                        tokens->push_back(Token(LITERAL, FLOAT_LITERAL, buffer, line_num, line_pos));
                    }
                    buffer = "";
                    continue;
                }
                
                look_next = look_ahead(cur_ind, line);
                cur_ind--; // bad logic, will fix later
                int check_operators_next = if_arr_contains(LOOK_FOR_OPERATORS, look_next);
                int check_separators_next = if_arr_contains(LOOK_FOR_SEPARATORS, look_next);
                if(look_next[0] == mcr_WHITESPACE_SPACE || look_next[0] == mcr_WHITESPACE_NEWLINE || 
                    look_next[0] == mcr_WHITESPACE_RETURN || look_next[0] == mcr_WHITESPACE_TAB ||
                    (buffer != "" && check_operators_next != -1 || check_separators_next != -1)
                    ){
                    // IDENTIFIER_UNKNOWN is a placeholder for now, explained in compiler.hpp
                    if(buffer[0] != 0x0){
                        tokens->push_back(Token(IDENTIFIER, IDENTIFIER_UNKNOWN, buffer, line_num, line_pos));
                    }
                    buffer = "";
                    continue;
                }

                // I don't remember why I did these if statements, 
                // I don't know if they are needed but don't want to find out
                // //this has to made so that 1+1, i++ and so on can be tokenized
                // //will be fixed later for better version, seems to work for now
                if(check_operators_next != -1){
                    check_operators(check_operators_next, tokens, buffer);
                    buffer = "";
                    continue;
                }
                // same as above
                if(check_separators_next != -1){
                    check_separators(check_separators_next, tokens, buffer);
                    buffer = "";
                    continue;
                }
                break;
            }
        }

        if(!in_block_comment){
            buffer = "";
        }
        line_pos = 0;
    }
    file.close();

    return tokens;
}

std::string look_ahead(size_t &cur_ind, std::string &line) {
    cur_ind++;
    if(cur_ind >= line.length())
        return "";
    else
        return line.substr(cur_ind, 1);
}

// These error messages will be replaced with a better version later
void check_separators(int x, std::vector<Token> *tokens, std::string &buffer) {
    if(buffer == "") return;
    switch (x){
        case 0: tokens->push_back(Token(SEPARATOR, LPAREN, buffer, line_num, line_pos)); break;
        case 1: tokens->push_back(Token(SEPARATOR, RPAREN, buffer, line_num, line_pos)); break;
        case 2: tokens->push_back(Token(SEPARATOR, LBRACE, buffer, line_num, line_pos)); break;
        case 3: tokens->push_back(Token(SEPARATOR, RBRACE, buffer, line_num, line_pos)); break;
        case 4: tokens->push_back(Token(SEPARATOR, LBRACKET, buffer, line_num, line_pos)); break;
        case 5: tokens->push_back(Token(SEPARATOR, RBRACKET, buffer, line_num, line_pos)); break;
        case 6: tokens->push_back(Token(SEPARATOR, SEMICOLON, buffer, line_num, line_pos)); break;
        case 7: tokens->push_back(Token(SEPARATOR, COMMA, buffer, line_num, line_pos)); break;
        case 8: tokens->push_back(Token(SEPARATOR, DOT, buffer, line_num, line_pos)); break;
        default: 
        message(TOKENIZER_SYNTAX, FL_compiler2, 
        "check_separators '" + buffer + "' at row: " 
        + std::to_string(line_num) + " @ " + std::to_string(line_pos) +
        " - code: " + std::to_string(x) + " not found in separators list."
        , true);
    }
}
void check_operators(int x, std::vector<Token> *tokens, std::string &buffer) {
    if(buffer == "") return;
    switch (x){
        case 0: tokens->push_back(Token(OPERATOR, ADD, buffer, line_num, line_pos)); break;
        case 1: tokens->push_back(Token(OPERATOR, SUB, buffer, line_num, line_pos)); break;
        case 2: tokens->push_back(Token(OPERATOR, MUL, buffer, line_num, line_pos)); break;
        case 3: tokens->push_back(Token(OPERATOR, DIV, buffer, line_num, line_pos)); break;
        case 4: tokens->push_back(Token(OPERATOR, ASSIGN, buffer, line_num, line_pos)); break;
        case 5: tokens->push_back(Token(OPERATOR, ADD_ASSIGN, buffer, line_num, line_pos)); break;
        case 6: tokens->push_back(Token(OPERATOR, SUB_ASSIGN, buffer, line_num, line_pos)); break;
        case 7: tokens->push_back(Token(OPERATOR, EQ, buffer, line_num, line_pos)); break;
        case 8: tokens->push_back(Token(OPERATOR, NEQ, buffer, line_num, line_pos)); break;
        case 9: tokens->push_back(Token(OPERATOR, GT, buffer, line_num, line_pos)); break;
        case 10: tokens->push_back(Token(OPERATOR, LT, buffer, line_num, line_pos)); break;
        case 11: tokens->push_back(Token(OPERATOR, GTE, buffer, line_num, line_pos)); break;
        case 12: tokens->push_back(Token(OPERATOR, LTE, buffer, line_num, line_pos)); break;
        case 13: tokens->push_back(Token(OPERATOR, AND, buffer, line_num, line_pos)); break;
        case 14: tokens->push_back(Token(OPERATOR, OR, buffer, line_num, line_pos)); break;
        case 15: tokens->push_back(Token(OPERATOR, NOT, buffer, line_num, line_pos)); break;
        case 16: tokens->push_back(Token(OPERATOR, BIT_AND, buffer, line_num, line_pos)); break;
        case 17: tokens->push_back(Token(OPERATOR, BIT_OR, buffer, line_num, line_pos)); break;
        case 18: tokens->push_back(Token(OPERATOR, BIT_XOR, buffer, line_num, line_pos)); break;
        case 19: tokens->push_back(Token(OPERATOR, BIT_NOT, buffer, line_num, line_pos)); break;
        case 20: tokens->push_back(Token(OPERATOR, LSHIFT, buffer, line_num, line_pos)); break;
        case 21: tokens->push_back(Token(OPERATOR, RSHIFT, buffer, line_num, line_pos)); break;
        case 22: tokens->push_back(Token(OPERATOR, MOD, buffer, line_num, line_pos)); break;
        case 23: tokens->push_back(Token(OPERATOR, INC, buffer, line_num, line_pos)); break;
        case 24: tokens->push_back(Token(OPERATOR, DEC, buffer, line_num, line_pos)); break;
        case 25: tokens->push_back(Token(OPERATOR, MUL_ASSIGN, buffer, line_num, line_pos)); break;
        case 26: tokens->push_back(Token(OPERATOR, DIV_ASSIGN, buffer, line_num, line_pos)); break;
        case 27: tokens->push_back(Token(OPERATOR, MOD_ASSIGN, buffer, line_num, line_pos)); break;
        default: 
        message(TOKENIZER_SYNTAX, FL_compiler2, 
        "check_operators '" + buffer + "' at row: " 
        + std::to_string(line_num) + " @ " + std::to_string(line_pos) +
        " - code: " + std::to_string(x) + " not found in operators list."
        , true);
    }
}

void check_keywords(int x, std::vector<Token> *tokens, std::string &buffer) {
    if(buffer == "") return;
    // will improve this later
    switch (x){
        case 0: tokens->push_back(Token(KEYWORD, KEYWORD_EXIT, buffer, line_num, line_pos)); break;
        case 1: tokens->push_back(Token(KEYWORD, KEYWORD_IF, buffer, line_num, line_pos)); break;
        case 2: tokens->push_back(Token(KEYWORD, KEYWORD_ELSE, buffer, line_num, line_pos)); break;
        case 3: tokens->push_back(Token(KEYWORD, KEYWORD_WHILE, buffer, line_num, line_pos)); break;
        case 4: tokens->push_back(Token(KEYWORD, KEYWORD_FOR, buffer, line_num, line_pos)); break;
        case 5: tokens->push_back(Token(KEYWORD, KEYWORD_RETURN, buffer, line_num, line_pos)); break;
        case 6: tokens->push_back(Token(KEYWORD, KEYWORD_INT, buffer, line_num, line_pos)); break;
        case 7: tokens->push_back(Token(KEYWORD, KEYWORD_STRING, buffer, line_num, line_pos)); break;
        case 8: tokens->push_back(Token(KEYWORD, KEYWORD_CHAR, buffer, line_num, line_pos)); break;
        case 9: tokens->push_back(Token(KEYWORD, KEYWORD_FLOAT, buffer, line_num, line_pos)); break;
        case 10: tokens->push_back(Token(KEYWORD, KEYWORD_DOUBLE, buffer, line_num, line_pos)); break;
        case 11: tokens->push_back(Token(KEYWORD, KEYWORD_BOOL, buffer, line_num, line_pos)); break;
        case 12: tokens->push_back(Token(KEYWORD, KEYWORD_TRUE, buffer, line_num, line_pos)); break;
        case 13: tokens->push_back(Token(KEYWORD, KEYWORD_FALSE, buffer, line_num, line_pos)); break;
        case 14: tokens->push_back(Token(KEYWORD, KEYWORD_FUNCTION, buffer, line_num, line_pos)); break;
        case 15: tokens->push_back(Token(KEYWORD, KEYWORD_STRUCT, buffer, line_num, line_pos)); break;
        case 16: tokens->push_back(Token(KEYWORD, KEYWORD_ENUM, buffer, line_num, line_pos)); break;
        case 17: tokens->push_back(Token(KEYWORD, KEYWORD_IMPORT, buffer, line_num, line_pos)); break;
        case 18: tokens->push_back(Token(KEYWORD, KEYWORD_MACRO, buffer, line_num, line_pos)); break;
        case 19: tokens->push_back(Token(KEYWORD, KEYWORD_COMPILER, buffer, line_num, line_pos)); break;
        case 20: tokens->push_back(Token(KEYWORD, KEYWORD_VOID, buffer, line_num, line_pos)); break;
        default: 
        message(TOKENIZER_SYNTAX, FL_compiler2, 
        "check_keywords '" + buffer + "' at row: " 
        + std::to_string(line_num) + " @ " + std::to_string(line_pos) +
        " - code: " + std::to_string(x) + " not found in keywords list."
        , true);
    }
}

// !UPDATE ERROR MESSAGE IF TAKEN INTO USE
// void check_preprocessor(int x, std::vector<Token> *tokens, std::string &buffer){
//     if(buffer == "") return;
//     switch (x){
//         case 0: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_IMPORT, buffer)); break;
//         case 1: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_MACRO, buffer)); break;
//         case 2: tokens->push_back(Token(PREPROCESSOR, PREPROCESSOR_COMPILER, buffer)); break;
//         default: 
//         message(TOKENIZER_SYNTAX, FL_compiler2, 
//         "check_preprocessor " + buffer + " at row: " 
//         + std::to_string(line_num) + " @ " + std::to_string(line_pos) +
//         " - code: " + std::to_string(x) + " not found in operators list."
//         , true);
//     }
// }

