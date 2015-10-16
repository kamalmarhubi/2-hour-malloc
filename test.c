#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "mymalloc.h"


int main(void) {
    char* s = mymalloc(128);
    strcpy(s, "lolwat");

    printf("%016llx\n", s);

    printf("free list before:\n");
    print_free_list();

    myfree(s);
    printf("free list after:\n");
    print_free_list();
}
