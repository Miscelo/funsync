#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/*Function return User ID of linux USER. root=0, sudo=1000*/
char *getUID(){
    char *cmd = "id -g";
    int status;       /*to check if all process well done.*/
    /*Open a pipe stream for reading data data from bash command.*/
    FILE *tmp = popen(cmd, "r");
    if(tmp == NULL){
        fprintf(stderr, "ERROR! No space on memory can be assigned.\n");
        exit(1);
    }
    char uID[6];
    fgets(uID, 6, tmp);     /*write pipestream to a char array.*/
    status = pclose(tmp);      /*close pipe stream with a status check.*/
    if(status == -1){
        fprintf(stderr, "User ID can not be cached!\n");;
    }
    return strtok(uID, "\n");    /* eliminate NEWLINE from fgets*/
}


void systemlog(int sysstate){
    char *user = getenv("USER");
    char *userID;
    userID = getUID();
    char logMessage[1024];
    char uid[6];
    strcpy(uid, userID); 
    openlog("funsync", LOG_PID, LOG_USER);
    /* system() command returns 0 if everything is right. */
    if(sysstate == 0){                            
        sprintf(logMessage, "Backup startet by user %s (uid=%s)", user, uid);
        syslog(LOG_INFO, logMessage);
    } else {
        syslog(LOG_ERR, "EXECUTION ERROR! Backup has not been started!");
    }
    closelog();
    
}



/*Function returns a pointer to a string of date and time -> format "20221107" */
const char *getdate(){
    struct tm *tm;
    char buffer[9];
    time_t now = time(NULL); // get system time
    tm = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y%m%d", tm); 
    char *dt = buffer;
    return dt;
}

