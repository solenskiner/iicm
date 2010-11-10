#ifndef SQL_MAIN_H
#define SQL_MAIN_H

#include <libpq-fe.h>

PGconn* pt_connect(char* host, char* port, char* dbname, char* user, char* pass);
void pt_disconnect(PGconn* connection);



#endif // SQL_MAIN_H
