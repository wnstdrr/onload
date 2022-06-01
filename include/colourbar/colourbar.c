#include "colourbar.h"
#include <stdio.h>
#include <stddef.h>

/* Determine how to output the bar array */
const char *BLOCK_ARRAY[MAX_COLOUR_SIZE] = {
        DRK_BLOCK,           BLOCK, RESET,
        RED_LGHT_BLOCK,      BLOCK, RESET,
        GREEN_DRK_BLOCK,     BLOCK, RESET,
        YELLOW_DRK_BLOCK,    BLOCK, RESET,
        BLUE_DRK_BLOCK,      BLOCK, RESET,
        MAG_DRK_BLOCK,       BLOCK, RESET,
        CYAN_DRK_BLOCK,      BLOCK, RESET,
        WHITE_LGHT_BLOCK,    BLOCK, RESET,
        LGHT_BLOCK,          BLOCK, RESET,
        RED_DRK_BLOCK,       BLOCK, RESET,
        GREEN_LGHT_BLOCK,    BLOCK, RESET,
        YELLOW_LGHT_BLOCK,   BLOCK, RESET,
        BLUE_LGHT_BLOCK,     BLOCK, RESET,
        MAG_LGHT_BLOCK,      BLOCK, RESET,
        CYAN_LGHT_BLOCK,     BLOCK, RESET,
        WHITE_DRK_BLOCK,     BLOCK, RESET
};

void Colourbar(const int rot) { 
    /* 6 for perfect vertical rectangle
     * 24 for perfect horizontal rectangle
     * probably a better method exits but im bad at math
     */
    size_t i;
    for (i = 0; i < MAX_COLOUR_SIZE; i++) {
        if (i % rot == 0) {
            fprintf(stdout, "%c", '\n');
        }
        fprintf(stdout, "%s", *(BLOCK_ARRAY + i));
    }
    fprintf(stdout, "%c", '\n');
}
