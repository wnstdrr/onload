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

char *Dist(void) {
    // return the current distro
    const int size = 0xa;
    char *buf = (char*)malloc(sizeof(char) * size);

    FILE *distro_stream;
    distro_stream = popen("lsb_release -is", "r");
    fgets(buf, size, distro_stream);

    return buf;
}

char* DeviceAddress(void) {
    const int size = 0xa;
    char *Host = (char*)malloc(sizeof(char) * size);
    char *IP;

    int Hostname;

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

char *Packages(void) {
    const int size = 0xa;
    char *Packages = (char*)malloc(sizeof(char)*size);

    // only supports whatever string you give popen
    // as your package count, automating in the future...
    FILE *PackageStream = popen("xbps-query -l | egrep -c '^ii' | tr -d '\n'", "r");

    while (fgets(Packages, size, PackageStream) != NULL) {
        continue;
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
    char *system_t   = Time();
    char *kernel     = Kernel();
    char *address    = DeviceAddress();
    char *osname     = Dist();

    info -> Packages = packages;
    info -> Terminal = terminal != NULL ? terminal : "n/a";
    info -> Desktop  = desktop  != NULL ? desktop  : "n/a";
    info -> Time     = system_t;
    info -> Kernel   = kernel;
    info -> osname   = osname;
    info -> ipv4     = address;
}

void OnloadResult(_SYS_INFO *info) {
    char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
        {COMPLETE, " Osname   ", SEPERATOR, " ",  info -> osname},
        {COMPLETE, " Kernel   ", SEPERATOR, " ",  info -> Kernel},
        {COMPLETE, " Desktop  ", SEPERATOR, " ",  info -> Desktop},
        {COMPLETE, " Pkgs     ", SEPERATOR, " ",  info -> Packages}, 
    };

    size_t i, j;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < MAX_RESULT_ROW; i++) {
            fprintf(stdout, "%s", RESULT[j][i]);
        }
        fprintf(stdout, "%c", '\n');
    }
}
