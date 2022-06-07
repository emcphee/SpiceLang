//
// Created by Ethan on 6/6/2022.
//

#include "spiceParser.h"
#include <cstring>

spiceParser::spiceParser(spiceLexer* _lexer) {
    lexer = _lexer;
    curToken = lexer->get_next_token();
    prevToken = nullptr;
}

spiceASTNode* spiceParser::create_tree(){
    return parse_statements();
}

spiceASTNode* spiceParser::parse_statements(){
    auto* compound = new spiceASTNode(AST_COMPOUND);
    spiceASTNode* ast_statement = parse_statement();
    compound->compound_value.push_back(ast_statement);

    while(curToken->type == TOKEN_SEMI){
        eat_token(TOKEN_SEMI);

        ast_statement = parse_statement();
        if(ast_statement){
            compound->compound_value.push_back(ast_statement);
        }
    }
    return compound;
}

spiceASTNode* spiceParser::parse_statement(){
    switch(curToken->type){
        case TOKEN_ID: return parse_id();
    }
    return (new spiceASTNode(AST_NO_OP));
}

spiceASTNode* spiceParser::parse_id(){
    if( strcmp(curToken->value.c_str(), "int") != 0 ){
        return parse_int_var_definition();
    }else if( strcmp(curToken->value.c_str(), "string") != 0 ){
        return parse_string_var_definition();
    }else{
        return parse_variable();
    }
}

spiceASTNode* spiceParser::parse_string_var_definition(){
    // eat the string keyword
    eat_token(TOKEN_ID);
    std::string var_name = curToken->value;
    eat_token(TOKEN_ID);
    auto* var_definition = new spiceASTNode(AST_VAR_DEFINITION);
    spiceASTNode* var_value;
    if(curToken->type == TOKEN_EQUALS){
        eat_token(TOKEN_EQUALS);
        var_value = parse_expression();
        var_definition->variable_initialized = true;
    }else if(curToken->type == TOKEN_SEMI){
        var_value = new spiceASTNode(AST_STRING);
        var_definition->variable_initialized = false;
    }else{
        std::cout << "Expected ; after variable declaration." << std::endl;
        exit(1);
    }

    var_definition->variable_contents = var_value;
    var_definition->variable_definition_variable_name = var_name;

    if(var_value->type != AST_STRING){
        std::cout << "Non-string assigned to string variable." << std::endl;
        exit(1);
    }

    return var_definition;
}

spiceASTNode* spiceParser::parse_int_var_definition(){
    // eat the int keyword
    eat_token(TOKEN_ID);
    std::string var_name = curToken->value;
    eat_token(TOKEN_ID);
    auto* var_definition = new spiceASTNode(AST_VAR_DEFINITION);
    spiceASTNode* var_value;
    if(curToken->type == TOKEN_EQUALS){
        eat_token(TOKEN_EQUALS);
        var_value = parse_expression();
        var_definition->variable_initialized = true;
    }else if(curToken->type == TOKEN_SEMI){
        var_value = new spiceASTNode(AST_INT);
        var_definition->variable_initialized = false;
    }else{
        std::cout << "Expected ; after variable declaration." << std::endl;
        exit(1);
    }

    var_definition->variable_contents = var_value;
    var_definition->variable_definition_variable_name = var_name;

    if(var_value->type != AST_INT){
        std::cout << "Non-int assigned to int variable." << std::endl;
        exit(1);
    }

    return var_definition;
}

spiceASTNode* spiceParser::parse_string(){
    auto* ast_string = new spiceASTNode(AST_STRING);
    ast_string->string_value = curToken->value;
    eat_token(TOKEN_STRING);
    return ast_string;
}

spiceASTNode* spiceParser::parse_int(){
    auto* ast_int = new spiceASTNode(AST_INT);
    ast_int->int_value = std::stoi(curToken->value);
    eat_token(TOKEN_INT);
    return ast_int;
}

void spiceParser::eat_token(token_type type){
    if(curToken->type == type){
        lexerToken* temp = prevToken;
        prevToken = curToken;
        curToken = lexer->get_next_token();
        delete temp;
    }else{
        std::cout << "Unexpected token " << curToken->value << ", with type" << curToken->type << std::endl;
        exit(1);
    }
}

spiceASTNode* spiceParser::parse_expression(){
    switch(curToken->type){
        case TOKEN_STRING: return parse_string();
        case TOKEN_ID: return parse_id();
        case TOKEN_INT: return parse_int();
        default:
            std::cout << "Expected expression, got " << curToken->value << " with type " << curToken->type << std::endl;
            exit(1);
    }
}

spiceASTNode* spiceParser::parse_variable(){
    std::string token_value = curToken->value;
    eat_token(TOKEN_ID);
    if(curToken->type == TOKEN_LPAREN){
        return parse_function_call();
    }else{
        auto* ast_var = new spiceASTNode(AST_VAR);
        ast_var->variable_name = token_value;
        return ast_var;
    }
}

spiceASTNode* spiceParser::parse_function_call(){
    auto* func_call = new spiceASTNode(AST_FUNC_CALL);
    func_call->function_call_name = prevToken->value;
    eat_token(TOKEN_LPAREN);

    spiceASTNode* ast_expr = parse_statement();
    func_call->function_args.push_back(ast_expr);

    while(curToken->type == TOKEN_COMMA){
        eat_token(TOKEN_COMMA);

        ast_expr = parse_statement();
        func_call->function_args.push_back(ast_expr);
    }
    eat_token(TOKEN_RPAREN);
    return func_call;
}