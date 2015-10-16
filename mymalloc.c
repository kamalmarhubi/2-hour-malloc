#include "mymalloc.h"
#include <stddef.h>

struct allocation {
    size_t size;
    struct allocation* next;  // only if free
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
