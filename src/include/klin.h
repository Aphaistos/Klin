#ifndef KLIN_H
#define KLIN_H
#include "parser.h"
#include "as_frontend.h"

void kln_compile(char* src);
void kln_compile_file(const char* file);

#endif