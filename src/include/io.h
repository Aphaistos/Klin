#ifndef KLIN_IO_H
#define KLIN_IO_H
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename);
void write_file(const char* filename, char* outbuffer);
#endif