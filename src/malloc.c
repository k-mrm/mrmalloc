#include <stdio.h>
#include <unistd.h>

#include "malloc.h"

static mem_header base;
static mem_header *freelist = NULL;

void *mrmalloc(size_t nbytes) {
    if(nbytes == 0) {
        return NULL;
    }

    /* size of 1unit == sizeof(mem_header) */
    size_t nunits = (nbytes + sizeof(mem_header) - 1) / sizeof(mem_header) + 1;
    printf("%zd units\n", nunits);

    mem_header *prev = freelist;

    if(freelist == NULL) { /* first call of malloc */
        freelist = &base;
        prev = &base;
        base.ptr = freelist;
        base.size = 0;
    }

    for(mem_header *p = prev->ptr; ; prev = p, p = prev->ptr) {
        if(p == freelist) {
            ;
        }
    }

    void *ptr = sbrk(nbytes);
    if(ptr == (void *)-1) {
        return NULL;
    }

    return ptr;
}

void mrfree(void *ptr) {
    if(ptr == NULL) {
        return;
    }
}
