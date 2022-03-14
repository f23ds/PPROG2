#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "stack_fDoble.h"

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

struct _Stack
{
    void **items;
    int top;
    int capacity;
};


