#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "./glb/message.hpp"
#include "./compiler.hpp"

/*+++
============================
TODO: ERROR->
    test("LOL", arg, arg2, arg3
    )
causes:
%%%%%%%%%%%%%%%%%% ATL MESSAGE %%%%%%%%%%%%%%%%%%
MESSAGE CODE: <17-9>
MESSAGE: Unknown identifier.
GIVEN SP_MESSAGE: <Invalid argument in unknown identifier fixer. Expected a declaration or a function call, got: 'arg3' from line: 12 column: 29 of type: 4 and subtype: 6>
%%%%%%%%%%%%%%%%%% END MESSAGE %%%%%%%%%%%%%%%%%%
because of the whitespace after the last argument
Type: 2 Subtype: 3 Value: (
Type: 3 Subtype: 2 Value: "LOL"
Type: 2 Subtype: 7 Value: ,
Type: 4 Subtype: 6 Value: arg
Type: 2 Subtype: 7 Value: ,
Type: 4 Subtype: 6 Value: arg2
Type: 2 Subtype: 7 Value: ,
Type: 4 Subtype: 6 Value: arg3
Type: 7 Subtype: 3 Value:
Type: 2 Subtype: 4 Value: )
============================


does something for:
type 4: subtype: 6 || IDENTIFIER_UNKNOWN
it can be atleast:
    - function declaration          # // DONE
    - variable declaration          # // DONE
    - variable assignment           # // DONE
    - function call                 # // DONE
    - macro definition              # // TODO: PLACE AT FIRST IF
    - import statement              # // TODO: PLACE AT FIRST IF
    - compiler directive            # // TODO: PLACE AT FIRST IF
    - struct declaration            # // TODO: PLACE AT FIRST IF
    - enum declaration              # // TODO: PLACE AT FIRST IF
    - function argument name        # // TODO: PLACE AT ELSE

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
        
        std::cout << "UNKNOWN IDENTIFIER: " << tokens[i].value << " INFO: " << 
        tokens[i+1].type << " "
        << tokens[i+1].subtype << " " << 
        tokens[i+1].value <<
        " <=== next | previous ===>"  <<
        tokens[i-1].type << " "
        << tokens[i-1].subtype << " " << 
        tokens[i-1].value << std::endl;
        
        // For declarations such as
        // function, variable, struct, enum, etc.
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
                || tokens[i-1].subtype == KEYWORD_STRING
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
                || tokens[i-1].subtype == KEYWORD_STRING
                )
                &&
                tokens[i+1].type == Tokens::OPERATOR
                && tokens[i+1].subtype == Operator_Tokens::ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::ADD_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::SUB_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::MUL_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::DIV_ASSIGN
                || tokens[i+1].subtype == Operator_Tokens::MOD_ASSIGN
            )
            {
                tokens[i].subtype = IDENTIFIER_VAR_DECL;
            }

            else if(
                // Macro definition
                tokens[i-1].subtype == KEYWORD_MACRO
            )
            {
                tokens[i].subtype = IDENTIFIER_MACRO;
            }

            else if(
                // Import statement
                tokens[i-1].subtype == KEYWORD_IMPORT
            )
            {
                tokens[i].subtype = IDENTIFIER_IMPORT;
            }

            else if(
                // Compiler directive
                tokens[i-1].subtype == KEYWORD_COMPILER
            )
            {
                tokens[i].subtype = IDENTIFIER_COMPILER;
            }

            else if(
                // Struct declaration
                tokens[i-1].subtype == KEYWORD_STRUCT
            )
            {
                tokens[i].subtype = IDENTIFIER_STRUCT;
            }

            else if(
                // Enum declaration
                tokens[i-1].subtype == KEYWORD_ENUM
            )
            {
                tokens[i].subtype = IDENTIFIER_ENUM;
            }
            else if(
                // Argument definitions in function declarations
                // TODO: Only support for basic types, add more?
                   tokens[i-2].type == Tokens::SEPARATOR
                && tokens[i-2].subtype == Separator_Tokens::COMMA
                || tokens[i-2].subtype == Separator_Tokens::LPAREN

                && tokens[i-1].type == Tokens::KEYWORD
                && tokens[i-1].subtype == KEYWORD_INT
                || tokens[i-1].subtype == KEYWORD_FLOAT
                || tokens[i-1].subtype == KEYWORD_CHAR
                || tokens[i-1].subtype == KEYWORD_BOOL
                || tokens[i-1].subtype == KEYWORD_STRING

                // Check for (string test) or (int test, int test2, ...)
                && tokens[i+1].type == Tokens::SEPARATOR
                && tokens[i+1].subtype == Separator_Tokens::COMMA
                || tokens[i+1].subtype == Separator_Tokens::RPAREN
            ) 
            {
                tokens[i].subtype = IDENTIFIER_ARGUMENT;
            }
            // 
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


        } 


        // For function calls and variable assignments
        else {
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
                // if it is parenthless function call
                // If not, then the next token must be a left parenthesis else: error

                // NOTE: This is a very bad way to check for function calls
                //    Needs more testing?
                   tokens[i-1].type == Tokens::WHITESPACE
                && tokens[i+1].type == Tokens::WHITESPACE
                || tokens[i-1].type == Tokens::WHITESPACE
                && tokens[i+1].type == Tokens::SEPARATOR
                || tokens[i+1].type == Separator_Tokens::LPAREN
            )
            {
                tokens[i].subtype = IDENTIFIER_FUNC_CALL;
            } 
            else if(
                // Argument names in function calls
                // TODO: Only support for basic types, add more?
                   tokens[i-1].type == Tokens::SEPARATOR
                && tokens[i-1].subtype == Separator_Tokens::COMMA
                || tokens[i-1].subtype == Separator_Tokens::LPAREN

                // && tokens[i-1].type == Tokens::KEYWORD
                // && tokens[i-1].subtype == KEYWORD_INT
                // || tokens[i-1].subtype == KEYWORD_FLOAT
                // || tokens[i-1].subtype == KEYWORD_CHAR
                // || tokens[i-1].subtype == KEYWORD_BOOL
                // || tokens[i-1].subtype == KEYWORD_STRING

                // Check for (string test) or (int test, int test2, ...)
                && tokens[i+1].type == Tokens::SEPARATOR
                && tokens[i+1].subtype == Separator_Tokens::COMMA
                || tokens[i+1].subtype == Separator_Tokens::RPAREN
            ) 
            {
                tokens[i].subtype = IDENTIFIER_ARGUMENT;
            }
            else {
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
