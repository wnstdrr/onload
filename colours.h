#ifndef _COLOURS_H
#define _COLOURS_H
#include<stddef.h>
#define CBARLIMIT(n) (n < 1 || n > 17 ? 0 : 1)

/* Block background colour pairs 
 * TODO: implement fg/bg colours e.g lightness_colour_fg/bg
 * */
#define light         "\033[90;100m"
#define dark          "\033[30;40m"

#define light_red     "\033[31;41m"
#define dark_red      "\033[91;101m"

#define light_green   "\033[92;102m"
#define dark_green    "\033[32;42m"

#define light_yellow  "\033[93;103m"
#define dark_yellow   "\033[33;43m"

#define light_blue    "\033[94;104m"
#define dark_blue     "\033[34;44m"

#define light_magenta "\033[95;105m"
#define dark_magenta  "\033[35;45m"

#define light_cyan    "\033[96;106m"
#define dark_cyan     "\033[36;46m"

#define light_white   "\033[37;47m"
#define dark_white    "\033[97;107m"

/* Block foreground colours pairs */
#define light_magenta_fg "\033[95m"
#define dark_magenta_fg  "\033[35m"

#define blink         "\033[5m"
#define reset         "\033[0m"

typedef const struct blk {
    size_t size;
    char *blk[][3];
} blk;
extern unsigned int cbar(unsigned int n);
#endif /* _COLOURS_H */
