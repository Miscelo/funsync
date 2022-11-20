#ifndef GOODYS_H_
#define GOODYS_H_



/*Function returns a pointer to a string of date and time -> format "20221107" */
const char *getdate();

/* Function write Backup status in file /var/log/syslog */
void systemlog(int sysstate);

/*Function devuelve la USER ID en un string. UID is a shell varible and not a environmental variable*/
char *getUID();

#endif