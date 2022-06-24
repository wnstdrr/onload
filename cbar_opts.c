#include "include/colourbar/colourbar.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    size_t index;
    for (index = C_BAR_MIN; index < C_BAR_MAX; index++) {
        fprintf(stdout, "BAR_OPT: %ld\n", index);
        cbar(index);
        if (!C_BAR_LIMIT(index)) {
            perror("Bar index out of range");
            exit(1);
        }
    }
    return 0;
}
