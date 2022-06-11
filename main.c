#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

#include <stdlib.h>

int main(void) {
    _sys_o *sys_o = (_sys_o*)malloc(sizeof(_sys_o));
    sys_O(sys_o);

    c_bar(24);
    output_O(sys_o);
    free(sys_o);
    return 0;
}
