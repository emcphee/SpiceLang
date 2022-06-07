//
// Created by Ethan on 6/6/2022.
//

#include "lexerToken.h"

#include <utility>


lexerToken::lexerToken(std::string _value, token_type _type){
    value = std::move(_value);
    type = _type;
}