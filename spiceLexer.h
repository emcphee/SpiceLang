//
// Created by Ethan on 6/6/2022.
//

#ifndef SPICECPP_SPICELEXER_H
#define SPICECPP_SPICELEXER_H

#include "lexerToken.h"

#include <string>
#include <iostream>
#include <cctype>

class spiceLexer {
    std::string input;
    int index;
    char curChar;

public:
    explicit spiceLexer(std::string const &text_input);
    ~spiceLexer() = default;

    // moves forward in the lexer until it gets the next token and returns it
    lexerToken *get_next_token();

private:
    // moves forward one character in the input string
    void advance();

    // returns true only if on null character or end of string
    bool completed();

    // skips all subsequent whitespace
    void ignore_whitespace();


    /* Collection functions */

    // includes all numeric types
    lexerToken *collect_numeric_type();

    // variable names and keywords
    lexerToken *collect_id();

    // strings
    lexerToken *collect_string();



};



#endif //SPICECPP_SPICELEXER_H
