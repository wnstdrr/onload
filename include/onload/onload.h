#ifndef _ONLOAD_H
#define _ONLOAD_H

#include "../colourbar/colourbar.h"

#define TIME_FMT       "%a %b %d %I:%M:%S %Y"
#define MAX_RESULT_COL 20 
#define MAX_RESULT_ROW 5

typedef struct _SYS_INFO {
    char *Packages;
    char *Terminal;
    char *Desktop;
    char *Time;
    char *Kernel;
    char *osname;
    char *ipv4;
} _SYS_INFO;

enum _distro_type {
    debian_linux = 1 << 0,
    arch_linux   = 1 << 1,
    void_linux   = 1 << 2,
    free_bsd     = 1 << 3
};

extern char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW];

extern char *Dist(void);
extern char *DeviceAddress(void);
extern char *Packages(void);
extern char *Terminal(void);
extern char *Desktop(void);
extern char *OnloadENV(const char *env);
extern void OnloadSYS(_SYS_INFO *info);
extern void OnloadResult(_SYS_INFO *info);
#endif /* _ONLOAD_H */
