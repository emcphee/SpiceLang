//
// Created by Ethan on 6/6/2022.
//

#ifndef SPICECPP_SPICEPARSER_H
#define SPICECPP_SPICEPARSER_H

#include "spiceLexer.h"
#include "spiceASTNode.h"
class spiceParser {
    spiceLexer* lexer;
    lexerToken* curToken;
    lexerToken* prevToken;

public:
    explicit spiceParser(spiceLexer* _lexer);
    spiceASTNode* create_tree();

private:
    // has an expected token to eat, if its expected, eat it, if it's not, exit(1)
    void eat_token(token_type type);

    spiceASTNode* parse_statements();
    spiceASTNode* parse_statement();
    spiceASTNode* parse_id();
    spiceASTNode* parse_string();
    spiceASTNode* parse_int();
    spiceASTNode* parse_string_var_definition();
    spiceASTNode* parse_int_var_definition();
    spiceASTNode* parse_expression();
    spiceASTNode* parse_variable();
    spiceASTNode* parse_function_call();
};


#endif //SPICECPP_SPICEPARSER_H
