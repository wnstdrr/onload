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

void output_O(_sys_o *info) {
    char *out_array[MAX_RESULT_COL][MAX_ROW_LEN] = {
        {COMPLETE, " Osname   ", SEPERATOR, " ",  info -> dist},
        {COMPLETE, " Kernel   ", SEPERATOR, " ",  info -> kernel},
        {COMPLETE, " Desktop  ", SEPERATOR, " ",  info -> desk},
        {COMPLETE, " Pkgs     ", SEPERATOR, " ",  info -> pkgs}, 
    };
    size_t col, row;
    for (col = 0; col < MAX_COL_LEN; col++) {
        for (row = 0; row < MAX_ROW_LEN; row++) {
            fprintf(stdout, "%s", out_array[col][row]);
        }
        fprintf(stdout, "%c", '\n');
    }
}

void sys_O(_sys_o *info) {
    char *terminal, *desktop, *pkgs, *date, *kernel, *addrv4, *dist;
    
    terminal = term_O();
    desktop  = desk_O();
    pkgs     = pkgs_O();
    date     = date_O();
    kernel   = kernel_O();
    addrv4   = dev_addr_v4_O();
    dist     = dist_O();

    info -> term    = terminal != NULL ? terminal : "n/a";
    info -> desk    = desktop  != NULL ? desktop  : "n/a";
    info -> pkgs    = pkgs     != NULL ? pkgs     : "n/a";
    info -> date    = date;
    info -> kernel  = kernel;
    info -> addr_v4 = addrv4;
    info -> dist    = dist;
}

char *env_O(const char *env) {
    char *e = getenv(env);
    return e == NULL ? '\0' : e;
}

char *term_O(void) {
    char *Term = env_O("TERM");
    return Term;
}

char *desk_O(void) {
    char *Desk = env_O("XDG_CURRENT_DESKTOP");
    return Desk;
}

char *pkgs_O(void) {
    const int size = 0xa;
    char *Packages = (char*)malloc(sizeof(char)*size);

    // only supports whatever string you give popen
    // as your package count, automating in the future...
    FILE *PackageStream = popen("xbps-query -l | egrep -c '^ii' | tr -d '\n'", "r");
    fgets(Packages, size, PackageStream);
    pclose(PackageStream);
    return Packages;
}

char *date_O(void) {
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

char *kernel_O(void) {
    struct utsname uname_info;
    uname(&uname_info);

    char * ReleaseName = uname_info . release;
    int PopcornSize = strlen(ReleaseName)+1;

    char *popcorn = (char*)malloc(sizeof(char)*PopcornSize);
    memcpy(popcorn, ReleaseName, PopcornSize);
    return popcorn;
}

char* dev_addr_v4_O(void) {
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

char *dist_O(void) {
    const int size = 0xa;
    char *buf = (char*)malloc(sizeof(char) * size);

    FILE *distro_stream;
    distro_stream = popen("lsb_release -is", "r");
    fgets(buf, size, distro_stream);
    pclose(distro_stream);
    return buf;
}
