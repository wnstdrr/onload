#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

#include <stdio.h>

int main(void) {
    _SYS_INFO sys_info;
    OnloadSYS(&sys_info);

    // Load Horizontal Colourbar & Results
    Colourbar(24);
    OnloadResult(&sys_info);
    return 0;
}
