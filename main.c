#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<syslog.h>
#include<regex.h>
#include "goodys.h"

typedef enum{false,true} bool;




/*Function writes log to system.*/
void systemlog(int i);

int main(int argc, char *argv[]){

    char dt[9];
    strcpy(dt, getdate());
    printf("Datum: %s\n", dt);

    systemlog(42);

    
    

    // printf("%s %02d %02d:%02d:%02d\n",month[tm.tm_mon], tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // system("rsync -n -av $BackupSource $BackupDestination");
    char word[12];
    fgets(word,12,stdin);
    printf("%s\n", word);


    return EXIT_SUCCESS;
}


void systemlog(int i){
    char *user = getenv("USER");
    int userID = 0;
    char line[1024];
    FILE *myf = fopen("/etc/passwd", "r");
    if(myf==NULL){
        fprintf(stderr, "Error: Failed to open file /etc/passwd!");
        userID=9999;
    } else {
        while (fgets(line , sizeof(line) , myf )!= NULL){
            if (strstr(line , user)!= NULL){
                printf("%s",line);
                
            }
        }
    }

    fclose(myf);
    
    openlog("funsync", LOG_PID, LOG_USER);
    if(i==42){
        char *info_message = strxcat("Start backup - by user ", user, "(uid=", userID, ")");
        syslog(LOG_INFO, info_message);
    }
    syslog(LOG_ERR, "NO access to files.");
    closelog();
}




