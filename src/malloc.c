#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

static mem_header base;
static mem_header *freep = NULL;

#define MINALLOC 1024

static mem_header *morecore(size_t nunits) {
    if(MINALLOC > nunits) {
        nunits = MINALLOC;
    }

    void *p = sbrk(sizeof(mem_header) * nunits);

    if(p == (void *)-1) return NULL;

    mem_header *up = (mem_header *)p;
    up->size = nunits;

    /* TODO: link to freelist */
    mrfree((void *)(up + 1));

    return freep;
}

void *mrmalloc(size_t nbytes) {
    if(nbytes == 0) {
        return NULL;
    }

    /* size of 1unit == sizeof(mem_header) */
    size_t nunits = (nbytes + sizeof(mem_header) - 1) / sizeof(mem_header) + 1;
    printf("%zd units\n", nunits);

    mem_header *prev = freep;

    if(freep == NULL) { /* first call of malloc */
        prev = freep = &base;
        base.ptr = freep;
        base.size = 0;
    }

    for(mem_header *p = prev->ptr; ; prev = p, p = prev->ptr) {
        if(p->size >= nunits) { /* enough */
            if(p->size == nunits) {
                prev->ptr = p->ptr;
            }
            else {
                p->size -= nunits;
                p += p->size;
                p->size = nunits;
            }
            freep = prev;
            return (void *)(p + 1);
        }

        if(p == freep) {
            if((p = morecore(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

void mrfree(void *ptr) {
    if(ptr == NULL) {
        return;
    }

    mem_header *bp = (mem_header *)ptr - 1;

    mem_header *p;
    for(p = freep; !(p < bp && bp < p->ptr); p = p->ptr) {
        if(p->ptr <= p && (p < bp || bp < p->ptr))
            break;
    }

    if(bp + bp->size == p->ptr) {
    /*
     *   ...@----@++++@****@---@+++++@---@...
     *      ^         ^    ^         ^
     *      p         bp   p->ptr    p->ptr->ptr
     */
        bp->size += p->ptr->size;
        bp->ptr = p->ptr->ptr;
    }
    else {
    /*
     *   ...@--@+++@****@++++@--@...
     *      ^      ^         ^
     *      p      bp        p->ptr
     */
        bp->ptr = p->ptr;
    }

    if(p + p->size == bp) {
    /*
     *   ...@----@*****@++++@--@...
     *      ^    ^          ^
     *      p    bp         bp->ptr
     */
        p->size += bp->size;
        p->ptr = bp->ptr;
    }
    else {
    /*
     *   ...@--@+++@****@++++@--@...
     *      ^      ^         ^
     *      p      bp        p->ptr
     */
        p->ptr = bp;
    }

    freep = p;
}
