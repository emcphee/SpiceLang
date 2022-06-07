//
// Created by Ethan on 6/6/2022.
//

#include "spiceLexer.h"

spiceLexer::spiceLexer(std::string const &text_input){
    if(text_input.length() == 0){
        std::cout << "Input file has a length of zero." << std::endl;
        exit(1);
    }

    this->input = text_input;
    this->index = 0;
    this->curChar = text_input[0];
}

void spiceLexer::advance(){
    if(!completed()){
        index++;
        curChar = input[index];
    }
}

bool spiceLexer::completed(){
    if(index >= input.length() || curChar == '\0'){
        return true;
    }else{
        return false;
    }
}

void spiceLexer::ignore_whitespace(){
    while( isspace(curChar) )
        advance();
}

lexerToken* spiceLexer::get_next_token(){
    while( !completed() ){
        ignore_whitespace();

        if( std::isdigit(curChar) )
            return collect_numeric_type();

        if(curChar == '"')
            return collect_string();

        if( std::isalnum(curChar) )
            return collect_id();

        token_type t;
        switch(curChar){
            case '=':
                t = TOKEN_EQUALS;
                break;
            case ';':
                t = TOKEN_SEMI;
                break;
            case '(':
                t = TOKEN_LPAREN;
                break;
            case ')':
                t = TOKEN_RPAREN;
                break;
            case ',':
                t = TOKEN_COMMA;
                break;
            default:
                continue;
        }
        std::string s;
        s.push_back(curChar);
        advance();
        auto *token = new lexerToken(s, t);
        return token;

    }
    auto* token = new lexerToken("\0", TOKEN_EOF);
    return token;
}


// just ints for now
lexerToken* spiceLexer::collect_numeric_type(){
    std::string s;
    while(std::isdigit(curChar) ){
        s.push_back(curChar);
        advance();
    }
    auto *token = new lexerToken(s, TOKEN_INT);
    return token;
}


lexerToken* spiceLexer::collect_id(){
    std::string s;
    while( std::isalnum(curChar) ){
        s.push_back(curChar);
        advance();
    }
    auto *token = new lexerToken(s, TOKEN_ID);
    return token;
}


lexerToken* spiceLexer::collect_string(){
    std::string s;

    // gets rid of the first "
    advance();

    char prev = 0;            // 92 is backslash
    while( curChar != '"' && prev != 92){
        s.push_back(curChar);
        prev = curChar;
        advance();
    }
    advance();
    auto *token = new lexerToken(s, TOKEN_STRING);
    return token;
}
