#include <sys/utsname.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "onload.h"
#include "../colourbar/colourbar.h" 

void OnloadSYS(_SYS_INFO *info) {
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
    struct utsname uname_info; 
    uname(&uname_info);

    char *Release    = uname_info . release;
    int ReleaseSize  = strlen(Release)+1;

    char *TERM       = getenv("TERM");
    char *DESKTOP    = getenv("XDG_CURRENT_DESKTOP"); 
   
    info -> Terminal = TERM     != NULL ? TERM              : "n/a";
    info -> Desktop  = DESKTOP  != NULL ? DESKTOP           : "n/a";
    info -> Time     = timeinfo != NULL ? asctime(timeinfo) : "n/a";
   
    memcpy(info -> Time,   TimeBuffer,  TimeBufferSize);
    memcpy(info -> Kernel, Release, ReleaseSize);
}

char *OnloadENV(const char *env) {
    // load a custom environment variable
    char * e = getenv(env);
    if (e == NULL) {
        return '\0';
    }
    return e;
}

void OnloadResult(_SYS_INFO *info) {
    char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
        {COMPLETE, " Terminal ", SEPERATOR, " ",  info -> Terminal},
        {COMPLETE, " Kernel   ", SEPERATOR, " ",  info -> Kernel},
        {COMPLETE, " Desktop  ", SEPERATOR, " ",  info -> Desktop},
        {COMPLETE, " Time     ", SEPERATOR, " ",  info -> Time}
    };

    size_t i, j;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 5; i++) {
            fprintf(stdout, "%s", RESULT[j][i]);
        }
        fprintf(stdout, "%c", '\n');
    }
}
