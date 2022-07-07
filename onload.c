#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

#include "config.h"
#include "onload.h"

#define max_row 8
#define GETSIZE(x) (sizeof x / sizeof *(x + 0))
#define CLEN(x) (sizeof(char) * x)

extern void 
onload_output(_sys_o *info) {
    register size_t col, row;
    register long unsigned int max_col;
    const char *out_array[][max_row] = {
        {completion, " ", "OS     ", seperator_colour, seperator, reset, " ", info->dist},
        {completion, " ", "Kernel ", seperator_colour, seperator, reset, " ", info->kernel},
        {completion, " ", "Term   ", seperator_colour, seperator, reset, " ", info->term},
        {completion, " ", "Date   ", seperator_colour, seperator, reset, " ", info->date},
        {completion, " ", "Uptime ", seperator_colour, seperator, reset, " ", info->sysup},
        {completion, " ", "Desk   ", seperator_colour, seperator, reset, " ", info->desk},
        {completion, " ", "Pkgs   ", seperator_colour, seperator, reset, " ", info->pkgs},
    };
    max_col = GETSIZE(out_array);
    const char *(*OUT)[][max_row] = &out_array;
    for (col = 0; col < max_col; col++) {
        for (row = 0; row < max_row; row++) {
            fprintf(stdout, "%s", *(*(*OUT + col) + row));
        }
        fprintf(stdout, "%c", '\n');
    }
    fprintf(stdout, "%s", endl);
}

extern void 
system_info(_sys_o *info) {
    char *term, *dsk, *pkgs, *datet, *kern, *dist, *sysup;

    term = terminal();
    dsk = desktop();
    pkgs = packages();
    datet = date();
    kern = kernel();
    dist = distro();
    sysup = userup();

    info->term = term != NULL ? term : "n/a";
    info->desk = dsk != NULL ? dsk : "n/a";
    info->pkgs = pkgs != NULL ? pkgs : "n/a";
    info->date = datet;
    info->kernel = kern;
    info->dist = dist;
    info->sysup = sysup;
}

extern inline _sys_o *
onload_struct(void) {
    _sys_o *sys_o;
    sys_o = (_sys_o *)malloc(sizeof(_sys_o));
    return sys_o;
}
extern inline void 
onload_free(void *ptr) { free(ptr); }

extern inline char *
environment(const char *env) {
    char *e;
    e = getenv(env);
    return e == NULL ? '\0' : e;
}

extern inline char *
terminal(void) {
    char *Term;
    Term = environment("TERM");
    return Term;
}

extern inline char *
desktop(void) {
    char *Desk;
    Desk = environment("XDG_CURRENT_DESKTOP");
    return Desk;
}

char *
packages(void) {
    const int size = 0x32;
    char *dist, *Packages;
    FILE *PackageStream;
    dist = distro();

    char pkgstring[size];
    register size_t i, j;
    int pkgstringLength;
    int distroFound = 0;

    char *(*pak)[][3] = &packs;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (strcmp(dist, *(*(*pak + i) + 0)) == 0) {
                pkgstringLength = strlen(*(*(*pak + i) + (j + 1))) + 1;
                memcpy(&pkgstring, (*(*(*pak + i) + (j + 1))),
                       CLEN(pkgstringLength));
                distroFound = 1;
                break;
            }
        }
    }
    if (distroFound != 1) {
        int pkgdefaultLength;
        pkgdefaultLength = strlen(defaultpkg) + 1;
        memcpy(&pkgstring, defaultpkg, pkgdefaultLength);
        distroFound = 1;
    }
    Packages = (char *)malloc(CLEN(size));
    PackageStream = popen(pkgstring, "r");
    if (fgets(Packages, size, PackageStream) == NULL) {
        return '\0';
    }
    pclose(PackageStream);
    return Packages;
}

char *
date(void) {
    int TimeBufferSize, strftimeResult;
    char *TimeBuffer;
    time_t now;
    struct tm *timeinfo;

    now = time(&now);
    timeinfo = localtime(&now);

    TimeBufferSize = 0xa;
    TimeBuffer = (char *)malloc(CLEN(TimeBufferSize));
    strftimeResult = strftime(TimeBuffer, TimeBufferSize, time_fmt, timeinfo);

    while (strftimeResult == 0) {
        free(TimeBuffer);
        TimeBufferSize *= 2;
        TimeBuffer = (char *)malloc(CLEN(TimeBufferSize));
        strftimeResult = strftime(TimeBuffer, TimeBufferSize, time_fmt, timeinfo);
    }
    return TimeBuffer;
}

char *
kernel(void) {
    struct utsname uname_info;
    uname(&uname_info);

    char *ReleaseName, *popcorn;
    int PopcornSize;
    ReleaseName = uname_info.release;
    PopcornSize = strlen(ReleaseName) + 1;

    popcorn = (char *)malloc(CLEN(PopcornSize));
    memcpy(popcorn, ReleaseName, PopcornSize);
    return popcorn;
}

char *
distro(void) {
    const int size = 0xa;
    char *buf;
    buf = (char *)malloc(CLEN(size));

    FILE *distro_stream;
    distro_stream = popen("lsb_release -is | tr -d '\n'", "r");
    if (fgets(buf, size, distro_stream) == NULL) {
        return '\0';
    }
    pclose(distro_stream);
    return buf;
}

char *
userup(void) {
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
    unsigned long long days, hours, minutes, seconds;
    const int size = 0xff;
    char *tmstr;
    tmstr = (char *)malloc(CLEN(size));

    seconds = tm.tv_sec;
    days = seconds / 86400;
    hours = seconds / 3600 - (days * 24);
    minutes = seconds / 60 - (days * 1440) - (hours * 60);

    if (days == 0 && hours == 0) {
        snprintf(tmstr, size, "%lldm", minutes);
    } else if (days == 0) {
        snprintf(tmstr, size, "%lldh %lldm", hours, minutes);
    } else {
        snprintf(tmstr, size, "%lldd %lldh %lldm", days, hours, minutes);
    }
    return tmstr;
}
