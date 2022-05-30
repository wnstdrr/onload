#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

#include <stdio.h>

int main(void) {
    _SYS_INFO sys_info;
    OnloadSYS(&sys_info);
    Colourbar(24);

    // temporary prints to mimic final result
    fprintf(stdout,
    "[%s] Terminal %s %s\n"
    "[%s] Kernel   %s %s\n"
    "[%s] Desktop  %s %s\n"
    "[%s] Time     %s %s", CHECK, ARROW, sys_info . Terminal, CHECK, ARROW, sys_info . Kernel, CHECK, ARROW, sys_info . Desktop, CHECK, ARROW, sys_info . Time);
    return 0;
}
