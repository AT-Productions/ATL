#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "./glb/message.hpp"
#include "./compiler.hpp"

/*+++
does something for:
type 4: subtype: 6 || IDENTIFIER_UNKNOWN
it can be a function or a variable, hopefully nothing else

syntax:
    Function declaration:
        <identifier> <identifier> (<identifier> <identifier> <identifier> ... <identifier>)
    Function call: 
        <identifier>
        <identifier>()
        <identifier>(<expression>)

    Function example:
        void print() {
            print("Hello, World!");
        }

        print       <- This can be done if no args are needed
        print()     <- Also valid

        print("Hello, World!")      <- If the function takes an argument, then of course it/they must be passed
        
        -> Hello, World!
           -u-
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Variable declaration:
        <identifier> <identifier>
        <identifier> <identifier> = <expression>
    
    Variable assignment:
        <identifier> = <expression>
    
    Variable example:
        int x
        int y = 5

        x           <- These will be interpeted as function calls, which will cause errors
        y           <- These will be interpeted as function calls, which will cause errors
        -> Error
           -u-
---*/

void IDENTIFIER_UNKNOWN_fix(std::vector<Token> &tokens){
    for (size_t i = 0; i < tokens.size(); i++) {
        if(tokens[i].type != Tokens::IDENTIFIER || 
            tokens[i].subtype != IDENTIFIER_UNKNOWN) continue;
        if(i - 1 < 0 || i + 1 >= tokens.size()) continue; // TODO: What if the first token is an unknown identifier or parenthesisless function call?
        
        std::cout << "UNKNOWN IDENTIFIER: " << tokens[i].value <<" " << 
        tokens[i+1].type << " "
        << tokens[i+1].subtype << " " << 
        tokens[i+1].value << std::endl;
        
        // For declarations
        if(tokens[i-1].type == Tokens::KEYWORD){
            if(
                // Function declaration
                // can be: INT, FLOAT, CHAR, BOOL, VOID
                // TODO: CHECK -> // NOTE: TABS ARE NOT ALLOWED?
                (
                   tokens[i-1].subtype == KEYWORD_INT 
                || tokens[i-1].subtype == KEYWORD_FLOAT 
                || tokens[i-1].subtype == KEYWORD_CHAR 
                || tokens[i-1].subtype == KEYWORD_BOOL 
                || tokens[i-1].subtype == KEYWORD_VOID
                )
                && 
                (
                   tokens[i+1].type == Tokens::SEPARATOR
                && tokens[i+1].subtype == Separator_Tokens::LPAREN
                )
            )
            {
                tokens[i].subtype = IDENTIFIER_FUNC_DECL;
            }


            else if(
                // Variable declaration
                (
                   tokens[i-1].subtype == KEYWORD_INT 
                || tokens[i-1].subtype == KEYWORD_FLOAT 
                || tokens[i-1].subtype == KEYWORD_CHAR 
                || tokens[i-1].subtype == KEYWORD_BOOL 
                )
                &&
                (
                    tokens[i+1].type == Tokens::OPERATOR
                    && tokens[i+1].subtype == Operator_Tokens::ASSIGN
                    || tokens[i+1].subtype == Operator_Tokens::ADD_ASSIGN
                    || tokens[i+1].subtype == Operator_Tokens::SUB_ASSIGN
                    || tokens[i+1].subtype == Operator_Tokens::MUL_ASSIGN
                    || tokens[i+1].subtype == Operator_Tokens::DIV_ASSIGN
                    || tokens[i+1].subtype == Operator_Tokens::MOD_ASSIGN
                    
                ) 
            )
            {
                tokens[i].subtype = IDENTIFIER_VAR_DECL;
            }
            else {
                message(
                    UNKNOW_IDENTIFIER,
                    FL_compiler253,
                    "Invalid argument in unknown identifier fixer. Expected a declaration, got: '" + tokens[i].value + 
                    "' from line: " + std::to_string(tokens[i].line) + " column: " + std::to_string(tokens[i].column)
                    + " of type: " + std::to_string(tokens[i].type) + " and subtype: " + std::to_string(tokens[i].subtype)
                    ,
                    true
                );
            }


        } else {
            if(
                // Variable assignment
                tokens[i+1].type == Tokens::OPERATOR
                && tokens[i+1].subtype == Operator_Tokens::ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::ADD_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::SUB_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::MUL_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::DIV_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::MOD_ASSIGN
            )
            {
                tokens[i].subtype = IDENTIFIER_VAR_ASSIGN;
            }
            else if(
                // Function call
                // Just in case previous and next tokens are whitespace

                // NOTE: This is a very bad way to check for function calls
                tokens[i-1].type == Tokens::WHITESPACE
                && tokens[i+1].type == Tokens::WHITESPACE
            )
            {
                tokens[i].subtype = IDENTIFIER_FUNC_CALL;
            } else {
                message(
                    UNKNOW_IDENTIFIER,
                    FL_compiler253,
                    "Invalid argument in unknown identifier fixer. Expected a declaration or a function call, got: '" + tokens[i].value + 
                    "' from line: " + std::to_string(tokens[i].line) + " column: " + std::to_string(tokens[i].column)
                    + " of type: " + std::to_string(tokens[i].type) + " and subtype: " + std::to_string(tokens[i].subtype)
                    ,
                    true
                );
            }
        }

    }
}