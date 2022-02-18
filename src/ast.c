#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>

AbstractTree* create_ast(int type) {
    AbstractTree* ast = calloc(1, sizeof(struct AST));
    ast->type = type;

    if(type == AST_COMPOUND) {
        ast->children = create_list(sizeof(struct AST*));
    }

    return ast;
}