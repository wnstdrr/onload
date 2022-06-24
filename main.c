#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

int main(void) {
    _sys_o *sys_o = (_sys_o*)sys_dyn_O();
    sys_O(sys_o);

    const ui n = 8;
    cbar(n);
    if (!C_BAR_LIMIT(n)) {
        return 1;
    }
    output_O(sys_o);
    free_O(sys_o);
    return 0;
}
