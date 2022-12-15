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

#define max_pathlength 1023

typedef struct _Sources_{
    char source[max_pathlength];
    struct _Sources_ *next;
}Sources;

typedef Sources *first;
typedef Sources *List;

/*Insert a new element to the list*/
void insert(List *list, char sourceline[max_pathlength]);
void copyFileToList(List *list, const char *sourcefile);


void printList(List list){
    printf("\n************     BACKUP FOLDERS    ***********\n");
    while(list != NULL){
        printf("%s\n", list->source);
            list = list->next;
    }
    printf("************************************************\n");
}


int main(int argc, char *argv[]){
    int sysstate;
    char dt[9];
    strcpy(dt, getdate());
    printf("Date: %s\n", dt);
    
    /* Create a linear list that stores all backup-paths from a file*/
    /* later , this list will be used in a loop to use rsync command*/
    List list = NULL;
    const char *sourcefile = "source.txt";
    copyFileToList(&list, sourcefile);
    printList(list);

    /* rsync -av  Transfer all files in Archive-Mode, ensures that devices, symbolic links , attributes, permissions,
       ownership are preserved in transfer. Also 'rsync -avz' will compressed it.
       rsync -avz /folder1 /folder2 /folder3 user@host::/home/user/backup   */
    char *systemcmd = "rsync -nav";
    char *backupsource = "~/Testfolder ~/Testfolder2";
    char *backupdestination = "~/Backup";
    char cmd[1024];
    sprintf(cmd, "%s %s %s", systemcmd, backupsource, backupdestination);
    sysstate = system(cmd);
    systemlog(sysstate);

    return EXIT_SUCCESS;
}


/*Insert a new element to the list that stores all backup paths*/
void insert(List *list, char sourceline[max_pathlength]){
    first new, actual;
    new = malloc(sizeof(Sources));
    if(new == NULL){
        fprintf(stderr, "Trouble to assign space on memory!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new->source, sourceline);
    if(*list == NULL){
        new->next = *list;
        *list = new;
    } else {
        actual = *list;
        while(actual->next!=NULL){
            actual = actual->next;
        }
        new->next = actual->next;
        actual->next = new;
    }
}



void copyFileToList(List *list, const char *sourcefile){
    char line[max_pathlength];
    const char nothing[1] = "";
    FILE *fread = fopen(sourcefile, "r");  
    if(fread == NULL){
        fprintf(stderr, "Trouble to open file with backup source!\n");
        exit(1);
    }else{
        while(fgets(line, sizeof(line), fread)!= NULL){
            char *q = strchr(line, '\n'); /* Kick out every new line character.*/ 
            if(q != NULL) *q = '\0';

            char *p = strchr(line, '#');  /* Ignore line if line contains symbol '#'.*/
            if((p == NULL) && (strcmp(nothing, line) != 0)){      /*kick out blanc lines.*/    
                    insert(list, line);
                
            }
        }
    }
    fclose(fread);
}



