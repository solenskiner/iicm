#include "sql_main.h"
#include <alloca.h>
#include <string.h>

PGconn* pt_connect(char* host, char* port, char* dbname, char* user, char* pass) {
  char *t_host, *t_port, *t_dbname, *t_user, *t_pass;

  if (host == NULL | *host == '\0') {
    t_host = (char*) alloca(sizeof(char) * 10);
    strncpy(t_host, "localhost", 10);
  } else
    t_host = host;

  if (port == NULL | *port == '\0') {
    t_port = (char*) alloca(sizeof(char) * 5);
    strncpy(t_port, "5432", 5);
  } else
    t_port = port;

  if (dbname == NULL | *dbname == '\0') {
    t_dbname = (char*) alloca(sizeof(char) * 6);
    strncpy(t_dbname, "PT3 DB", 6);
  } else
    t_dbname = dbname;

  if (user == NULL | *user == '\0') {
    t_user = (char*) alloca(sizeof(char) * 9);
    strncpy(t_user, "postgres", 9);
  } else
    t_user = user;

  if (pass == NULL | *pass == '\0') {
    t_pass = (char*) alloca(sizeof(char) * 7);
    strncpy(t_pass, "dbPass", 7);
  } else
    t_pass = pass;

  PGconn* connection = PQsetdbLogin(t_host,
                                   t_port,
                                   NULL,
                                   NULL,
                                   t_dbname,
                                   t_user,
                                   t_pass);
  if (PQstatus(connection) != CONNECTION_OK) {
    pt_disconnect(connection);
  }
  return connection;
}

void pt_disconnect(PGconn* connection) {
  PQfinish(connection);
  connection = NULL;
}

/*
PGresult *res = PQexec(connection, "blablabla");
PQclear(res);
*/
