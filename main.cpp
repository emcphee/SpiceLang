#include <iostream>
#include <fstream>
#include <sstream>
#include "spiceParser.h"

/*
 * enum token_type
{
    TOKEN_ID,    0
    TOKEN_EQUALS,1
    TOKEN_SEMI,  2
    TOKEN_LPAREN,3
    TOKEN_RPAREN,4
    TOKEN_STRING,5
    TOKEN_COMMA, 6
    TOKEN_EOF,   7
    TOKEN_INT    8
};
*/

std::string file_to_string(std::string filepath){
    std::ifstream t(filepath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int main() {
    std::string filepath = "../examples/sample.spice";
    std::string input_text = file_to_string(filepath);

    spiceLexer lexer = spiceLexer(input_text);
    spiceParser parser = spiceParser(lexer, lexerToken(__cxx11::basic_string(), TOKEN_STRING));

    std::cout << parser.get_token().value << std::endl;
}
