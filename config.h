#ifndef _CONFIG_H
#define _CONFIG_H 
#include "colours.h"

/* Unicode Characters */
#define block         "\u2588\u2588\u2588"
#define seperator     "\033[95m->\033[0m"
#define completion    "[\033[92m\u2713\033[0m]"

/* Seperator colour: default light_magenta*/
#define seperator_colour light_magenta_fg

/* Time format string, controls strftime for date */
#define time_fmt "%a %b %d %I:%M:%S %Y"

/* Endline at end of program execution: default "\n"*/
#define endl "\n"
                          /* background     style  endline*/
blk blkstruct = { .blk = { { dark,          block, reset },
                           { light_red,     block, reset },
                           { dark_green,    block, reset },
                           { dark_yellow,   block, reset },
                           { dark_blue,     block, reset },
                           { dark_magenta,  block, reset },
                           { dark_cyan,     block, reset },
                           { light_white,   block, reset },
                           { light,         block, reset },
                           { dark_red,      block, reset },
                           { light_green,   block, reset },
                           { light_yellow,  block, reset },
                           { light_blue,    block, reset },
                           { light_magenta, block, reset },
                           { light_cyan,    block, reset },
                           { dark_white,    block, reset } } };

/* Package manager strings for package counts, passed to popen */
char *defaultpkg = "dpkg -l | egrep '^ii' | wc -l | tr -d '\n'";    /* Default package string, Debian */
char *packs[][3]
    = { { "VoidLinux", "xbps-query -l | egrep -c '^ii' | tr -d '\n'" },
        { "Arch", "pacman -Q | wc -l | tr -d '\n'" } };
#endif /* _CONFIG_H */
