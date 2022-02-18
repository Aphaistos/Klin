#ifndef KLIN_AST_H
#define KLIN_AST_H
#include "list.h"

typedef struct AST {
    enum {
        AST_COMPOUND,
        AST_FUNCTION,
        AST_CALL,
        AST_ASSIGNMENT = 99,
        AST_DEFINITION_TYPE,
        AST_VARIABLE,
        AST_INT,
        AST_BINOP,
        AST_NOOP,
    } type;

    List* children;
    char* name;
    struct AST* value;
    int int_value;
    int dtype;
} AbstractTree;

AbstractTree* create_ast(int type);

#endif