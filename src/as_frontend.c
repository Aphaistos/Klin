#include "include/as_frontend.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* as_f_compound(AbstractTree* ast) {
    char* value = calloc(1, sizeof(char));
    for(int i = 0; i < ast->children->size; i++) {
        AbstractTree* child_ast = (AbstractTree*) ast->children->items[i];
        char* next_value = as_f(child_ast);
        value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
    }

    return value;
}
char* as_f_assignment(AbstractTree* ast) {

}
char* as_f_variable(AbstractTree* ast) {

}
char* as_f_call(AbstractTree* ast) {

}
char* as_f_int(AbstractTree* ast) {

}

char* as_f(AbstractTree* ast) {
    char* value = calloc(1, sizeof(char));
    char* next_value = 0;

    switch (ast->type) {
        case AST_COMPOUND: next_value = as_f_compound(ast); break;
        case AST_ASSIGNMENT: next_value = as_f_assignment(ast); break;
        case AST_VARIABLE: next_value = as_f_variable(ast); break;
        case AST_CALL: next_value = as_f_call(ast); break;
        case AST_INT: next_value = as_f_int(ast); break;
        default: { printf("[As Fronted]: No fronted for ast with type %d !\n", ast->type); exit(1); } break;
    }

    value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
    strcat(value, next_value);

    return value;
}