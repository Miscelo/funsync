#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>


char *strxcat(char *str, ...){
    if (str == NULL)
        return NULL;

    int totlen = strlen(str);     //wir definieren erste Argument länge 
    va_list lenlist, strlist;     // wir definieren 2 listen
    va_start (lenlist, str);      // starten werden wir beim ersten ARgument
    va_copy (strlist, lenlist);   //wir kopieren die eine Liste in eine 2.
    
    char *p = va_arg(lenlist, char *);    //Wir definieren unser 'START'-p für den while-loop
    while (p){                            //so lange Argumente vorhanden sind ....
        totlen += strlen (p);
        p = va_arg (lenlist, char *);     // geh zum nächsten argument
    };
    va_end (lenlist);
    char *newstr = malloc (totlen);
    if(newstr == NULL){
        printf("ERROR, not enough space!\n");
        exit(1);
    }
    strcpy(newstr, str);                //copieren wir das erste argument in den neuen String
    p = va_arg (strlist, char *);

    while(p){                          // im While-loop konkatenaten wir ein argument nach den anderen an den String 
        strcat(newstr, p); 
        p = va_arg (strlist, char *);
    }

    va_end(strlist);
    return newstr;
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