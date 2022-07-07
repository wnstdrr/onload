#include "colours.h"
#include "onload.h"

int 
main(void) {
    _sys_o *sys_o = (_sys_o *)onload_struct();
    system_info(sys_o);

    const unsigned int n = 8;
    cbar(n);
    if (!CBARLIMIT(n)) {
        return 1;
    }
    onload_output(sys_o);
    onload_free(sys_o);
    return 0;
}
