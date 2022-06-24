#ifndef _COLOURBLOCK_H
#define _COLOURBLOCK_H

#include <stddef.h>

#define MAX_COLOUR_COL  16
#define MAX_COLOUR_ROW  3

#define C_BAR_MIN       1
#define C_BAR_MAX       17

#define C_BAR_LIMIT(n) (n < C_BAR_MIN || n > C_BAR_MAX ? 0 : 1)

/* Unicode Characters */
#define BLOCK           "\u2588\u2588\u2588"
#define SEPERATOR       "\033[95m\u279C\033[0m"
#define COMPLETE        "[\033[92m\u2713\033[0m]"

/* BLOCK Colour definitions */
#define LGHT_BLOCK        "\033[90;100m"
#define DRK_BLOCK         "\033[30;40m"

#define RED_LGHT_BLOCK    "\033[31;41m"
#define RED_DRK_BLOCK     "\033[91;101m"

#define GREEN_LGHT_BLOCK  "\033[92;102m"
#define GREEN_DRK_BLOCK   "\033[32;42m"

#define YELLOW_LGHT_BLOCK "\033[93;103m"
#define YELLOW_DRK_BLOCK  "\033[33;43m"

#define BLUE_LGHT_BLOCK   "\033[94;104m"
#define BLUE_DRK_BLOCK    "\033[34;44m"

#define MAG_LGHT_BLOCK    "\033[95;105m"
#define MAG_DRK_BLOCK     "\033[35;45m"

#define CYAN_LGHT_BLOCK   "\033[96;106m"
#define CYAN_DRK_BLOCK    "\033[36;46m"

#define WHITE_LGHT_BLOCK  "\033[37;47m"
#define WHITE_DRK_BLOCK   "\033[97;107m"

#define BLINK           "\033[5m"
#define RESET           "\033[0m"

typedef unsigned int ui;
typedef char *c_p;
typedef const struct blk {size_t index; c_p block[][MAX_COLOUR_ROW];} blk;

extern ui cbar(const ui n);
#endif /* _COLOURBLOCK_H */
