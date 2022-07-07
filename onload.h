#ifndef _ONLOAD_H
#define _ONLOAD_H

typedef struct {
    char *term;
    char *desk;
    char *pkgs;
    char *date;
    char *kernel;
    char *dist;
    char *sysup;
} _sys_o;
extern void onload_output(_sys_o *info);
extern void system_info(_sys_o *info);

extern _sys_o *onload_struct(void);
extern void onload_free(void *ptr);

extern char *environment(const char *env);
extern char *terminal(void);
extern char *desktop(void);
extern char *packages(void);
extern char *date(void);
extern char *kernel(void);
extern char *distro(void);
extern char *userup(void);
#endif /* _ONLOAD_H */
