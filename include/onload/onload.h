#ifndef _ONLOAD_H
#define _ONLOAD_H

#include "../colourbar/colourbar.h"

#define TIME_FMT       "%X"
#define MAX_RESULT_COL 15 
#define MAX_RESULT_ROW 5

typedef struct _SYS_INFO {
    char *Terminal;
    char *Desktop;
    char *Time;
    char *Arch;
    char *Kernel;
} _SYS_INFO;

extern char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW];
extern void OnloadSYS(_SYS_INFO *info);
extern void OnloadResult(_SYS_INFO *info);
#endif /* _ONLOAD_H */
