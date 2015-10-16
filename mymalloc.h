#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stddef.h>

void *mymalloc(size_t size);
void myfree(void *ptr);
void *mycalloc(size_t nmemb, size_t size);
void *myrealloc(void *ptr, size_t size);

void print_free_list();
#endif  // MYMALLOC_H
