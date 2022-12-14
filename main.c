#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<syslog.h>
#include<regex.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <unistd.h>
#include "goodys.h"



int main(int argc, char *argv[]){
    int sysstate;
    char dt[9];
    strcpy(dt, getdate());
    printf("Date: %s\n", dt);
    
    char *systemcmd = "rsync -av";
    char *backupsource = "~/Testfolder ~/Testfolder2";
    char *backupdestination = "~/Backup";
    char cmd[1024];
    sprintf(cmd, "%s %s %s", systemcmd, backupsource, backupdestination);
    sysstate = system(cmd);
    systemlog(sysstate);

    return EXIT_SUCCESS;
}





