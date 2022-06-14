#include "colourbar.h"
#include <stdio.h>
#include <stddef.h>

/* Determine how to output the bar array */
const char *BLOCK_ARRAY[MAX_COLOUR_COL][MAX_COLOUR_SIZE] = {
    {DRK_BLOCK,           BLOCK, RESET},
    {RED_LGHT_BLOCK,      BLOCK, RESET},
    {GREEN_DRK_BLOCK,     BLOCK, RESET},
    {YELLOW_DRK_BLOCK,    BLOCK, RESET},
    {BLUE_DRK_BLOCK,      BLOCK, RESET},
    {MAG_DRK_BLOCK,       BLOCK, RESET},
    {CYAN_DRK_BLOCK,      BLOCK, RESET},
    {WHITE_LGHT_BLOCK,    BLOCK, RESET},
    {LGHT_BLOCK,          BLOCK, RESET},
    {RED_DRK_BLOCK,       BLOCK, RESET},
    {GREEN_LGHT_BLOCK,    BLOCK, RESET},
    {YELLOW_LGHT_BLOCK,   BLOCK, RESET},
    {BLUE_LGHT_BLOCK,     BLOCK, RESET},
    {MAG_LGHT_BLOCK,      BLOCK, RESET},
    {CYAN_LGHT_BLOCK,     BLOCK, RESET},
    {WHITE_DRK_BLOCK,     BLOCK, RESET}
};

signed int cbar(const int n) { 
    size_t col, row;
    if (C_BAR_LIMIT(n) == 1) {
        return -1;
    }
    for (col = 0; col < MAX_COLOUR_COL; col++) {
        if (col % n == 0) {
            fprintf(stdout, "%c", '\n');
        }
        for (row = 0; row < MAX_COLOUR_ROW; row++) { 
            fprintf(stdout, "%s", *(*(BLOCK_ARRAY + col) + row));
        }
    }
    fprintf(stdout, "%c", '\n');
    return 0;
}
