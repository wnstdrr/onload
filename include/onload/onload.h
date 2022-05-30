#ifndef _ONLOAD_H
#define _ONLOAD_H

#define TIME_FMT "%I:%M:%S"

typedef struct _SYS_INFO {
    char *Terminal;
    char *Desktop;
    char *Time;
    char *Arch;
    char *Kernel;
} _SYS_INFO;

extern void OnloadSYS(_SYS_INFO *info);
#endif /* _ONLOAD_H */
