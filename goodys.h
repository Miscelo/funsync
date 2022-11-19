#ifndef GOODYS_H_
#define GOODYS_H_




char *strxcat(char *str, ...);


/*Function returns a pointer to a string of date and time -> format "20221107" */
const char *getdate();


/*Function devuelve la USER ID en un string. UID is a shell varible and not a environmental variable*/
char *getUID();

#endif