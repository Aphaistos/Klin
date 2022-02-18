#ifndef KLIN_LIST_H
#define KLIN_LIST_H
#include <stdlib.h>

typedef struct LIST {
    void** items;
    size_t size;
    size_t item_size;
} List;

List* create_list(size_t item_size);

void list_push(List* list, void* item);

#endif