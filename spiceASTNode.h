//
// Created by Ethan on 6/6/2022.
//

#ifndef SPICECPP_SPICEASTNODE_H
#define SPICECPP_SPICEASTNODE_H

#include <string>
#include <vector>

enum AST_type{
    AST_VAR_DEFINITION, // variable definition

    AST_VAR, // variable reference

    AST_FUNC_CALL, // function call

    AST_STRING, // string
    AST_INT, // 4byte int

    AST_COMPOUND, // basically an array of statements

    AST_NO_OP // AST NO OPERATION
};



class spiceASTNode {
public:
    explicit spiceASTNode(AST_type _type);

    AST_type type;
    bool variable_initialized;

    /* AST_VAR_DEFINITION */
    std::string variable_definition_variable_name;
    spiceASTNode* variable_contents;

    /* AST_VAR */
    std::string variable_name;

    /* AST_FUNC_CALL */
    std::string function_call_name;
    std::vector<spiceASTNode*> function_args;

    /* AST_STRING */
    std::string string_value;

    /* AST_INT */
    int int_value;

    /* AST_COMPOUND */
    std::vector<spiceASTNode*> compound_value;
};


#endif //SPICECPP_SPICEASTNODE_H
