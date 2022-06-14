#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

int main(void) {
    _sys_o *sys_o = (_sys_o*)sys_dyn_O();
    sys_O(sys_o);

    signed int bar;
    bar = cbar(8);
    if (bar < 0) {
        return 1;
    }

    output_O(sys_o);
    free_O(sys_o);
    return 0;
}
