#include "mymalloc.h"
#include <stddef.h>


struct metadata {
    size_t next_sbrk;  // next amount sbrk by
    void* next_alloc;  // next allocation if can't be filled from free list
    struct allocation *free_list;
};


struct allocation {
    size_t size;
    struct allocation* next;  // only if free
    char data[1];
};


static struct metadata md = {
    .next_sbrk = 1024,
    .free_list = NULL,
};


void *mymalloc(size_t size) {
    return NULL;
}


void myfree(void *ptr) {
}


void *mycalloc(size_t nmemb, size_t size) {
    return NULL;
}


void *myrealloc(void *ptr, size_t size) {
    return NULL;
}
