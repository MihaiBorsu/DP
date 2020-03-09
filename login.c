#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

sqlite3 *db;
int rc;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callback2(void *data, int argc, char **argv, char **azColName) {
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void create_table(){
  char *zErrMsg = 0;
  char *sql = "CREATE TABLE USERS("	     \
      "ID INT PRIMARY KEY NOT NULL," \
      "NAME TEXT NOT NULL," \
      "PASSWORD TEXT NOT NULL," \
      "IP CHAR(16) NOT NULL," \
      "MAC CHAR(50) NOT NULL );";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
  } else {
      fprintf(stdout, "Table created successfully\n");
  }
  sqlite3_close(db);

}

void insert(){
   char *zErrMsg = 0;

  char *sql = "INSERT INTO USERS (ID,NAME,PASSWORD,IP,MAC) " \
    "VALUES (5, 'Paul', '32', 'California', '20000.00' ); ";


  
  
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
  } else {
      fprintf(stdout, "Records created successfully\n");
  }
}

static void select2(){
  char *zErrMsg = 0;
  const char* data = "Callback function called";
   char *sql = "SELECT * from USERS";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback2, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
}

int main(void) {
  char *zErrMsg = 0;
  rc = sqlite3_open("test.db", &db);
   
  if( rc ) {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  }
  else {
     fprintf(stderr, "Opened database successfully\n");
  }

  
  //create_table();
  insert();
  select2();
}
