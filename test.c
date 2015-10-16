#include <unistd.h>
#include <stdio.h>
#include "mymalloc.h"


int main(void) {
    printf("%016llx\n", mymalloc(20));

    printf("%016llx\n", sbrk(0));
    printf("%016llx\n", sbrk(1024));
    printf("%016llx\n", sbrk(0));
}
