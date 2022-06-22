#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "onload.h"
#include "../colourbar/colourbar.h" 

extern void output_O(_sys_o *info) {
    register size_t col, row;
    register long unsigned int MAX_COL_LEN;
    const char *out_array[][MAX_ROW_LEN] = {
        {COMPLETE, " Osname   ", SEPERATOR, " ",  info -> dist},
        {COMPLETE, " Kernel   ", SEPERATOR, " ",  info -> kernel},
        {COMPLETE, " Uptime   ", SEPERATOR, " ",  info -> sysup},
        {COMPLETE, " Pkgs     ", SEPERATOR, " ",  info -> pkgs},
        {COMPLETE, " Date     ", SEPERATOR, " ",  info -> date}
    };
    MAX_COL_LEN = sizeof(out_array) / sizeof(*(out_array + 0));
    const char *(*OUT)[][MAX_ROW_LEN] = &out_array;
    for (col = 0; col < MAX_COL_LEN; col++) {
        for (row = 0; row < MAX_ROW_LEN; row++) {
            fprintf(stdout, "%s", *(*(*OUT + col) + row));
        }
        fprintf(stdout, "%c", '\n');
    }
}

extern void sys_O(_sys_o *info) {
    char *terminal, *desktop, *pkgs, *date, *kernel, *addrv4, *dist, *sysup;
    
    terminal = term_O();
    desktop  = desk_O();
    pkgs     = pkgs_O();
    date     = date_O();
    kernel   = kernel_O();
    addrv4   = dev_addr_v4_O();
    dist     = dist_O();
    sysup    = sysup_O();

    info -> term    = terminal != NULL ? terminal : "n/a";
    info -> desk    = desktop  != NULL ? desktop  : "n/a";
    info -> pkgs    = pkgs     != NULL ? pkgs     : "n/a";
    info -> date    = date;
    info -> kernel  = kernel;
    info -> addr_v4 = addrv4;
    info -> dist    = dist;
    info -> sysup   = sysup;
}

extern inline _sys_o *sys_dyn_O(void) {
    _sys_o *sys_o;
    sys_o = (_sys_o*)malloc(sizeof(_sys_o));
    return sys_o;
}
extern inline void free_O(void *ptr) {
    free(ptr);
}

extern inline char *env_O(const char *env) {
    char *e; 
    e = getenv(env);
    return e == NULL ? '\0' : e;
}

extern inline char *term_O(void) {
    char *Term ;
    Term = env_O("TERM");
    return Term;
}

extern inline char *desk_O(void) {
    char *Desk;
    Desk = env_O("XDG_CURRENT_DESKTOP");
    return Desk;
}

char *pkgs_O(void) {
    const int size = 0x32;
    char *dist, *Packages;
    FILE *PackageStream;
    dist = dist_O();

    char pkgstring[size];
    char *defaultpkg = "dpkg -l | egrep '^ii' | wc -l | tr -d '\n'";
    char *packs[][3] = {
        {"VoidLinux", "xbps-query -l | egrep -c '^ii' | tr -d '\n'"},
        {"Arch", "pacman -Q | wc -l | tr -d '\n'"}
    };
    register size_t i, j;
    int pkgstringLength;
    int distroFound = 0;

    char *(*pak)[][3] = &packs;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (strcmp(dist, *(*(*pak + i) + 0)) == 0) {
                pkgstringLength = strlen( *(*(*pak + i)  + (j + 1) ) )+1;
                memcpy(&pkgstring, (*(*(*pak + i) + (j + 1) )), sizeof(char) * pkgstringLength);
                distroFound = 1;
                break;
            }
        }
    }
    if (distroFound != 1) {
        int pkgdefaultLength;
        pkgdefaultLength = strlen(defaultpkg)+1;
        memcpy(&pkgstring, defaultpkg, pkgdefaultLength);
        distroFound = 1;
    }
    Packages = (char*)malloc(sizeof(char) * size);
    PackageStream = popen(pkgstring, "r");
    if (fgets(Packages, size, PackageStream) == NULL) {
        return '\0';
    }
    pclose(PackageStream);
    return Packages;
}

char *date_O(void) {
    int TimeBufferSize, strftimeResult;
    char *TimeBuffer;
    time_t now;
    struct tm *timeinfo; 
    
    now = time(&now);
    timeinfo = localtime(&now);

    TimeBufferSize = 0xa;
    TimeBuffer = (char*)malloc(sizeof(char)*TimeBufferSize);
    strftimeResult = strftime(TimeBuffer, TimeBufferSize, TIME_FMT, timeinfo);

    while (strftimeResult == 0) {
       free(TimeBuffer);
       TimeBufferSize *= 2;
       TimeBuffer = (char*)malloc(sizeof(char) * TimeBufferSize);
       strftimeResult = strftime(TimeBuffer, TimeBufferSize, TIME_FMT, timeinfo);
    } 
    return TimeBuffer;
}

char *kernel_O(void) {
    struct utsname uname_info;
    uname(&uname_info);

    char *ReleaseName, *popcorn;
    int PopcornSize;
    ReleaseName = uname_info . release;
    PopcornSize = strlen(ReleaseName)+1;

    popcorn = (char*)malloc(sizeof(char) * PopcornSize);
    memcpy(popcorn, ReleaseName, PopcornSize);
    return popcorn;
}

char* dev_addr_v4_O(void) {
    const int size = 0xa;
    char *Host, *IP;
    int Hostname;
    Host = (char*)malloc(sizeof(char) * size);

    struct hostent *HostInfo;
    Hostname = gethostname(Host, sizeof(Host)); 
    if (Hostname <= 0) {
        return '\0';
    }
    strncat(Host, ".local", 0x7);
    HostInfo = gethostbyname(Host);
    IP = inet_ntoa(*(struct in_addr*)HostInfo -> h_addr_list[0]);
    return IP;
}

char *dist_O(void) {
    const int size = 0xa;
    char *buf;
    buf = (char*)malloc(sizeof(char) * size);

    FILE *distro_stream;
    distro_stream = popen("lsb_release -is | tr -d '\n'", "r");
    if (fgets(buf, size, distro_stream) == NULL) {
        return '\0';
    }
    pclose(distro_stream);
    return buf;
}

char *sysup_O(void) {
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
    unsigned long long days, hours, minutes, seconds;
    const int size = 0xff;
    char *tmstr;
    tmstr = (char*)malloc(sizeof(char) * size);

    seconds = tm . tv_sec;
    days    = seconds / 86400;
    hours   = seconds / 3600 - (days * 24);
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
