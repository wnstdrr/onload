#include <sys/utsname.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

   info -> Terminal = getenv("TERM"); 
   info -> Desktop  = getenv("XDG_CURRENT_DESKTOP");
   info -> Time     = asctime(timeinfo);

   memcpy(info -> Kernel, Release, ReleaseSize);
}
