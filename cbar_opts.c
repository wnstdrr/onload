#include "include/colourbar/colourbar.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    size_t index;
    signed int bar;
    for (index = C_BAR_MIN; index < C_BAR_MAX; index++) {
        fprintf(stdout, "BAR_OPT: %ld", index);
        bar = cbar(index);
        if (bar < 0) {
            perror("Bar index out of range");
            exit(1);
        }
    }
    return 0;
}
