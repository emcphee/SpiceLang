//
// Created by Ethan on 6/6/2022.
//

#ifndef SPICECPP_LEXERTOKEN_H
#define SPICECPP_LEXERTOKEN_H

#include <string>

enum token_type
{
    TOKEN_ID,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_STRING,
    TOKEN_COMMA,
    TOKEN_EOF,
    TOKEN_INT
};


class lexerToken {
public:

    lexerToken(std::string _value, token_type _type);

    token_type type;
    std::string value;

};


#endif //SPICECPP_LEXERTOKEN_H
