
#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h> // for size_t
typedef struct Vector_info
{
    size_t capacity;
    size_t size;
    int *ptr_to_mem;
} vector;
int *push_back(vector *);
void pop_back(vector *);
void init(vector *vec);
void destruct(vector *vec);
#endif
