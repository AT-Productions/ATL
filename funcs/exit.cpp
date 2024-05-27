#include "../glb/message.hpp"
#include "../compiler.hpp"

/*+++
ran when exit found. go to line end fill information and return to lexanalysis
---*/
void funcs_exit(std::string &buffer, std::vector<Token> &tokens, 
                int &line_num, std::string &line, int &cur_ind) {
    bool action = true;
    Tokens type = KEYWORD;
    int subtype = -1;
    std::string value = "";
    while(action){

    }
}