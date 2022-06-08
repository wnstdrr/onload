#include "include/colourbar/colourbar.h"
#include "include/onload/onload.h"

#include <stdlib.h>

int main(void) {
    _SYS_INFO sys_info;
    OnloadSYS(&sys_info);

    // Load Horizontal Colourbar & Results
    Colourbar(24);
    OnloadResult(&sys_info);
   
    /* Release dynamic memory from strut members */
    free(sys_info . Packages);
    free(sys_info . Time);
    free(sys_info . Kernel);
    return 0;
}
