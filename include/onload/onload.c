#include <sys/utsname.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "onload.h"
#include "../colourbar/colourbar.h" 


char *Packages(void) {
    /* DISCLAIMER:
     * if you really care this slows the program down
     * by about 0.037ms because popen supplied command is slow...
     * */
    const int size = 0xa;
    char *Packages = (char*)malloc(sizeof(char)*size);

    // assumes debian distro for now **the easy way**
    // will probably add support for others later but
    // that gets tedious with all the package managers.
    FILE *PackageStream = popen("dpkg -l | egrep -c '^ii' | tr -d '\n'", "r");
    if (PackageStream == NULL) {
        Packages[size] = '\0';
    }

    while (fgets(Packages, size, PackageStream) != NULL) {
        Packages[size] = '\0';
    }
    pclose(PackageStream);
    return Packages;
}

char *OnloadENV(const char *env) {
    // load a custom environment variable
    char *e = getenv(env);
    if (e == NULL) {
        return '\0';
    }
    return e;
}

char *Terminal(void) {
    char *Term = OnloadENV("TERM");
    return Term;
}

char *Desktop(void) {
    char *Desk = OnloadENV("XDG_CURRENT_DESKTOP");
    return Desk;
}

char *Time(void) {
    time_t now = time(&now);
    struct tm *timeinfo = localtime(&now);

    int TimeBufferSize = 0xa;
    char *TimeBuffer = (char*)malloc(sizeof(char)*TimeBufferSize);
    int strftimeResult = strftime(TimeBuffer, TimeBufferSize, TIME_FMT, timeinfo);

    while (strftimeResult == 0) {
       free(TimeBuffer);
       TimeBufferSize *= 2;
       TimeBuffer = (char*)malloc(sizeof(char)*TimeBufferSize);
       strftimeResult = strftime(TimeBuffer, TimeBufferSize, TIME_FMT, timeinfo);
    } 
    return TimeBuffer;
}

char *Kernel(void) {
    struct utsname uname_info;
    uname(&uname_info);

    char * ReleaseName = uname_info . release;
    int PopcornSize = strlen(ReleaseName)+1;

    char *popcorn = (char*)malloc(sizeof(char)*PopcornSize);
    memcpy(popcorn, ReleaseName, PopcornSize);
    return popcorn;
}

void OnloadSYS(_SYS_INFO *info) {
    char *terminal   = Terminal();
    char *desktop    = Desktop(); 
    char *packages   = Packages();
    char *time       = Time();
    char *kernel     = Kernel();

    info -> Packages = packages;
    info -> Terminal = terminal != NULL ? terminal : "n/a";
    info -> Desktop  = desktop  != NULL ? desktop  : "n/a";
    info -> Time     = time;
    info -> Kernel   = kernel;
}

void OnloadResult(_SYS_INFO *info) {
    char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
        {COMPLETE, " Terminal ", SEPERATOR, " ",  info -> Terminal},
        {COMPLETE, " Kernel   ", SEPERATOR, " ",  info -> Kernel},
        {COMPLETE, " Pkgs     ", SEPERATOR, " ",  info -> Packages},
        {COMPLETE, " Desktop  ", SEPERATOR, " ",  info -> Desktop},
        {COMPLETE, " Time     ", SEPERATOR, " ",  info -> Time}
    };

    size_t i, j;
    for (j = 0; j < 5; j++) {
        for (i = 0; i < MAX_RESULT_ROW; i++) {
            fprintf(stdout, "%s", RESULT[j][i]);
        }
        fprintf(stdout, "%c", '\n');
    }
}
