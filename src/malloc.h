#ifndef MRMALLOC_H
#define MRMALLOC_H

#include <stdio.h>

typedef union mem_header mem_header;

union mem_header {
    struct {
        mem_header *ptr;
        size_t size;
    };
    long align;
};

void *mrmalloc(size_t);
void mrfree(void *);

#endif
