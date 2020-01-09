#include <stdio.h>
#include <unistd.h>

#include "malloc.h"

void *mrmalloc(size_t nbytes) {
    if(nbytes == 0) {
        return NULL;
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
