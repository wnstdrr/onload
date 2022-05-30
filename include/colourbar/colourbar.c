#include "colourbar.h"
#include <stdio.h>
#include <stddef.h>

/* Determine how to output the bar array */
const char *BAR_ARRAY[MAX_COLOUR_SIZE] = {
        DRK_BAR,           BAR, RESET,
        RED_LGHT_BAR,      BAR, RESET,
        GREEN_DRK_BAR,     BAR, RESET,
        YELLOW_DRK_BAR,    BAR, RESET,
        BLUE_DRK_BAR,      BAR, RESET,
        MAG_DRK_BAR,       BAR, RESET,
        CYAN_DRK_BAR,      BAR, RESET,
        WHITE_LGHT_BAR,    BAR, RESET,
        LGHT_BAR,          BAR, RESET,
        RED_DRK_BAR,       BAR, RESET,
        GREEN_LGHT_BAR,    BAR, RESET,
        YELLOW_LGHT_BAR,   BAR, RESET,
        BLUE_LGHT_BAR,     BAR, RESET,
        MAG_LGHT_BAR,      BAR, RESET,
        CYAN_LGHT_BAR,     BAR, RESET,
        WHITE_DRK_BAR,     BAR, RESET
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
        fprintf(stdout, "%s", *(BAR_ARRAY + i));
    }
    fprintf(stdout, "%c", '\n');
}
