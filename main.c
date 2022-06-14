#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

#include <stdlib.h>
#include <stdio.h>
int main(void) {
    _sys_o *sys_o = (_sys_o*)malloc(sizeof(_sys_o));
    sys_O(sys_o);

    signed int bar = cbar(8);
    if (bar < 0) {
        perror("Bar index out of range: 1..17");
        exit(1);
    }
    output_O(sys_o);
    free(sys_o);
    return 0;
}
