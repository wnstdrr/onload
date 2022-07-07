#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "colours.h"
enum {barmin = 1, barmax = 17};
int 
main(void) {
    register size_t index;
    for (index = barmin; index < barmax; index++) {
        fprintf(stdout, "BAR_OPT: %ld\n", index);
        cbar(index);
        if (!CBARLIMIT(index)) {
            perror("Bar index out of range");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
