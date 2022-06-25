#ifndef _ONLOAD_H
#define _ONLOAD_H

#define TIME_FMT    "%a %b %d %I:%M:%S %Y"
#define MAX_ROW_LEN 6

typedef struct _sys_o {
    char *term;
    char *desk;
    char *pkgs;
    char *date;
    char *kernel;
    char *dist;
    char *sysup;
} _sys_o;

extern const char *out_array[][MAX_ROW_LEN];
extern void output_O(_sys_o *info);
extern void sys_O(_sys_o *info);

extern _sys_o *sys_dyn_O(void);
extern void free_O(void *ptr);

extern char *env_O(const char *env);
extern char *term_O(void);
extern char *desk_O(void);
extern char *pkgs_O(void);
extern char *date_O(void);
extern char *kernel_O(void);
extern char *dist_O(void);
extern char *sysup_O(void);
#endif /* _ONLOAD_H */
