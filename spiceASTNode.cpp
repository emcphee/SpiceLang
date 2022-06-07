//
// Created by Ethan on 6/6/2022.
//

#include "spiceASTNode.h"

spiceASTNode::spiceASTNode(AST_type _type) {
    type = _type;
    variable_contents = nullptr;
    int_value = 0;
    variable_initialized = false;
}
