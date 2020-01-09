#ifndef MRMALLOC_H
#define MRMALLOC_H

#include <stdio.h>

union mem_header {
    struct {
        union mem_header *ptr;
        size_t size;
    };
    long align;
};

void *mrmalloc(size_t);
void mrfree(void *);

#endif
