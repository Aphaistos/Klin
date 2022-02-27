#ifndef KLIN_AS_FRONTED_H
#define KLIN_AS_FRONTED_H
#include "ast.h"

char* as_f_compound(AbstractTree* ast);
char* as_f_function(AbstractTree* ast);
char* as_f_variable(AbstractTree* ast);
char* as_f_call(AbstractTree* ast);
char* as_f_int(AbstractTree* ast);
char* as_f_root(AbstractTree* root);
char* as_f(AbstractTree* ast);
#endif