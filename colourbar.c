#include "config.h"
#include <stdio.h>

enum { max_column = 16, max_row = 3 };
inline unsigned int 
cbar(const unsigned int n) {
    if (!CBARLIMIT(n)) {
        return 1;
    }
    register size_t col, row;
    for (col = 0; col < max_column; col++) {
        if (col % n == 0 && col != 0) {
            fprintf(stdout, "%c", '\n');
        }
        for (row = 0; row < max_row; row++) {
            fprintf(stdout, "%s", blkstruct.blk[col][row]);
        }
    }
    fprintf(stdout, "%c", '\n');
    return 0;
}
