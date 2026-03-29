#include <stdio.h>
#include "xmalloc.h"


int main(int argc, char *argv[]) {
    xmalloc_init();
    void *data_ptr = (void *)malloc(10);

    // xfree(data_ptr);
    xmalloc_print();

    xmalloc_deinit();
    return 0;
}