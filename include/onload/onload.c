#include <sys/utsname.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "onload.h"
#include "../colourbar/colourbar.h" 

void OnloadSYS(_SYS_INFO *info) {
   // load uname system information 
   time_t now;
   struct tm *timeinfo;
   time(&now);
   timeinfo = localtime(&now);

   struct utsname uname_info; 
   uname(&uname_info);

   char *Release    = uname_info . release;
   int ReleaseSize  = strlen(Release)+1;

   char *TERM       = getenv("TERM");
   char *DESKTOP    = getenv("XDG_CURRENT_DESKTOP"); 
   
   info -> Terminal = TERM     != NULL ? TERM              : "n/a";
   info -> Desktop  = DESKTOP  != NULL ? DESKTOP           : "n/a";
   info -> Time     = timeinfo != NULL ? asctime(timeinfo) : "n/a";

   memcpy(info -> Kernel, Release, ReleaseSize);
}

void OnloadResult(_SYS_INFO *info) {
    char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
        {CHECK, " Terminal ", ARROW, " ",  info -> Terminal},
        {CHECK, " Kernel   ", ARROW, " ",  info -> Kernel},
        {CHECK, " Desktop  ", ARROW, " ",  info -> Desktop},
        {CHECK, " Time     ", ARROW, " ",  info -> Time}
    };

    size_t i, j;
    for (j = 0; j < 4; j++) {
        // Column
        for (i = 0; i < 5; i++) {
            // Row
            fprintf(stdout, "%s", RESULT[j][i]);
        }
        fprintf(stdout, "%c", '\n');
    }
}
