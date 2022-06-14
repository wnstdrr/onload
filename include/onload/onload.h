#ifndef _ONLOAD_H
#define _ONLOAD_H

#include "../colourbar/colourbar.h"

#define TIME_FMT       "%a %b %d %I:%M:%S %Y"
#define MAX_RESULT_COL 20 

#define MAX_COL_LEN 5
#define MAX_ROW_LEN 5

typedef struct _sys_o {
    char *term;
    char *desk;
    char *pkgs;
    char *date;
    char *kernel;
    char *addr_v4;
    char *dist;
    char *sysup;
} _sys_o;

extern char *out_array[MAX_RESULT_COL][MAX_ROW_LEN];
extern void output_O(_sys_o *info);
extern void sys_O(_sys_o *info);

extern char *env_O(const char *env);
extern char *term_O(void);
extern char *desk_O(void);
extern char *pkgs_O(void);
extern char *date_O(void);
extern char *kernel_O(void);
extern char *dev_addr_v4_O(void);
extern char *dist_O(void);
extern char *sysup_O(void);
#endif /* _ONLOAD_H */
