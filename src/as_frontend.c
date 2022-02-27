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
        strcat(value, next_value);
    }

    return value;
}
char* as_f_function(AbstractTree* ast) {
    char* s = calloc(1, sizeof(char));
    const char* template =  ".globl %s\n"
                            "%s:\n";
    s = realloc(s, (strlen(template) + (strlen(ast->name) * 2) + 1) * sizeof(char));
    sprintf(s, template, ast->name, ast->name);

    char* as_val = as_f(ast->value);

    s = realloc(s, (strlen(s) + strlen(as_val) + 1) * sizeof(char));
    strcat(s, as_val);

    return s;
}
char* as_f_variable(AbstractTree* ast) {
    char* s = calloc(1, sizeof(char));
    return s;
}
char* as_f_call(AbstractTree* ast) {
    char* s = calloc(1, sizeof(char));
    if(strcmp(ast->name, "return") == 0) { // is function "return"
        AbstractTree* return_arg = (AbstractTree*) ast->value->children->size ? ast->value->children->items[0] : (void*) 0;
        const char* template =  "mov $%d, %%eax\n"
                                "ret\n";
        char* ret_s = calloc(strlen(template) + 128, sizeof(char));
        sprintf(ret_s, template, return_arg ? return_arg->int_value : 0);
        s = realloc(s, (strlen(ret_s) + 1) * sizeof(char));
        strcat(s, ret_s);
    }

    return s;
}
char* as_f_int(AbstractTree* ast) {
    char* s = calloc(1, sizeof(char));
    return s;
}
char* as_f_root(AbstractTree* root) {
    const char* section_text =  "\n.section .text\n"
                                ".globl _start\n"
                                "_start:\n"
                                "call main\n"
                                "mov \%eax, \%ebx\n"
                                "mov $1, \%eax\n"
                                "int $0x80\n";
    char* value = as_f(root);
    value = (char*) realloc(value, (strlen(value) + strlen(section_text) + 1) * sizeof(char));
    strcat(value, section_text);
    /*char* value = (char*) calloc(strlen(section_text) + 128,  sizeof(char));
    strcpy(value, section_text);

    char* next_value = as_f(root);
    value = (char*) realloc(value, (strlen(value) + strlen(next_value) + 1) * sizeof(char));
    strcat(value, next_value);
*/
    return value;
}
char* as_f(AbstractTree* ast) {
    char* value = calloc(1, sizeof(char));
    char* next_value = 0;


    switch (ast->type) {
        case AST_COMPOUND: next_value = as_f_compound(ast); break;
        case AST_VARIABLE: next_value = as_f_variable(ast); break;
        case AST_CALL: next_value = as_f_call(ast); break;
        case AST_INT: next_value = as_f_int(ast); break;
        case AST_FUNCTION: next_value = as_f_function(ast); break;
        default: { printf("[As Fronted]: No fronted for ast with type %d !\n", ast->type); exit(1); } break;
    }

    value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
    strcat(value, next_value);

    return value;
}