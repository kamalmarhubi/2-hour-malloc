#include "mymalloc.h"
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>


struct metadata {
    size_t next_sbrk;  // next amount sbrk by
    void* next_alloc;  // next allocation if can't be filled from free list
    struct allocation *free_list;
};


struct allocation {
    size_t size;
    struct allocation* next;  // only if free
    char data[1];  // the data given to the caller
};


static struct metadata md = {
    .next_sbrk = 1024,
    .next_alloc = NULL,
    .free_list = NULL,
};


void print_free_list() {
    printf("in free list\n");
    struct allocation* alloc;
    for(alloc = md.free_list; alloc; alloc = alloc->next) {
        printf("%016llx\t%016llx\n", alloc, alloc->size);
    }
    printf("end free list\n");
}


size_t remaining_space() {
    char* alloc_loc = md.next_alloc;
    char* curr_brk = sbrk(0);

    return curr_brk - alloc_loc;
}


size_t required(size_t size) {
    return size + sizeof(struct allocation);
}


// Check if an allocation of size can be made without moving program break. This
// check includes the size of the allocation struct.
bool fits_without_sbrk(size_t size) {
    return remaining_space() > required(size);
}


bool fits_with_sbrk(size_t size) {
    char* curr_brk = sbrk(0);
    char* alloc_loc = md.next_alloc;
    return (curr_brk + md.next_sbrk - alloc_loc) > size;
}


// Ensures that an allocation of size is possible, extending program data space
// if necessary.
int ensure_fits(size_t size) {
    // TODO: figure out where to put this... initializer?
    if (!md.next_alloc) { md.next_alloc = sbrk(0); }
    if (fits_without_sbrk(size)) {
        return;
    }

    size_t next_sbrk = md.next_sbrk;

    while(!fits_with_sbrk(size)) {
        md.next_sbrk *= 2;
    }

    // TODO: error handling
    sbrk(md.next_sbrk);

    return 0;
}


// Returns the pointer to struct allocation that ptr is the data member of.
//
// Does no sanity checking.
//
// TODO: change this to a macro?
struct allocation* alloc_of(void* ptr) {
    char *p = (char*) ptr;
    return (struct allocation*) (p - offsetof(struct allocation, data));
}


void *mymalloc(size_t size) {
    // TODO: add looking at freelist
    ensure_fits(size);

    struct allocation* alloc = md.next_alloc;
    alloc->size = size;
    alloc->next = NULL;

    md.next_alloc += required(size);

    return alloc->data;
}


void myfree(void *ptr) {
    printf("in free\n");
    struct allocation* alloc = alloc_of(ptr);
    printf("in free2\n");
    printf("alloc: %016llx\n", alloc);
    printf("alloc.next: %016llx\n", alloc->next);
    alloc->next = md.free_list;
    printf("alloc: %016llx\n", alloc);
    printf("in free3\n");
    md.free_list = alloc;
}


void *mycalloc(size_t nmemb, size_t size) {
    return NULL;
}


void *myrealloc(void *ptr, size_t size) {
    return NULL;
}
