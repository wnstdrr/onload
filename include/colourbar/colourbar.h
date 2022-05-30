#ifndef _COLOURBAR_H
#define _COLOURBAR_H

#define MAX_COLOUR_SIZE 48

/* Unicode Characters */
#define BAR             "\u2588\u2588\u2588"
#define ARROW           "\033[95m\u2794\033[0m"
#define CHECK           "\033[92m\u2714\033[0m"

/* BAR Colour definitions */
#define LGHT_BAR        "\033[90;100m"
#define DRK_BAR         "\033[30;40m"

#define RED_LGHT_BAR    "\033[31;41m"
#define RED_DRK_BAR     "\033[91;101m"

#define GREEN_LGHT_BAR  "\033[92;102m"
#define GREEN_DRK_BAR   "\033[32;42m"

#define YELLOW_LGHT_BAR "\033[93;103m"
#define YELLOW_DRK_BAR  "\033[33;43m"

#define BLUE_LGHT_BAR   "\033[94;104m"
#define BLUE_DRK_BAR    "\033[34;44m"

#define MAG_LGHT_BAR    "\033[95;105m"
#define MAG_DRK_BAR     "\033[35;45m"

#define CYAN_LGHT_BAR   "\033[96;106m"
#define CYAN_DRK_BAR    "\033[36;46m"

#define WHITE_LGHT_BAR  "\033[37;47m"
#define WHITE_DRK_BAR   "\033[97;107m"

#define BLINK           "\033[5m"
#define RESET           "\033[0m"

extern const char *BAR_ARRAY[MAX_COLOUR_SIZE];
extern void Colourbar(const int rot);

#endif /* _COLOURBAR_H */
