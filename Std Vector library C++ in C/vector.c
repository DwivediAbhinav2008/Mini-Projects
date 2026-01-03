
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "vector.h"
#include "flushinput.h"
#include "input.h"
/* Push element */
int *push_back(vector *temp_v)
{
    int element_to_insert;
    while (1)
    {
        read_int("\nEnter element to insert ", &element_to_insert);
        if (errno != 0)
        {
            continue;
        }
        else
            break;
    }

    if (temp_v->size == temp_v->capacity)
    {
        int *temp_ptr =
            (int *)realloc(temp_v->ptr_to_mem,
                           (temp_v->capacity * 2) * sizeof(int));

        if (!temp_ptr)
            return NULL;

        temp_v->ptr_to_mem = temp_ptr;
        temp_v->capacity *= 2;
    }

    temp_v->ptr_to_mem[temp_v->size] = element_to_insert;
    temp_v->size++;

    puts("\nElement inserted");
    return temp_v->ptr_to_mem;
}

/* Pop element */
void pop_back(vector *temp_v)
{
    if (temp_v->size == 0)
    {
        fprintf(stderr , "\nNo element\n");
        return;
        
    }
    temp_v->size--;
    puts("\nPopped last element");
}
/*Initialize a vector */
void init(vector *vec)
{
    vec->capacity = 100;
    vec->size = 0;
    vec->ptr_to_mem = (int *)malloc(vec->capacity * sizeof(int));
}

/* Destroy vector */
void destruct(vector *vec)
{
    vec->capacity = 0;
    vec->size = 0;
    free(vec->ptr_to_mem);
}
