#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static char* callback2(void *data, int argc, char **argv, char **azColName) {
   int i;
   //char result[255] = "";
   fprintf(stderr, "%s: \n", (const char*)data);
   for(i = 0; i<argc; i++) {
      //strcat(result, argv[i] ? argv[i] : "NULL");
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void create_table(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ) 
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   else 
      fprintf(stdout, "Opened database successfully\n");
   

  char *sql = "CREATE TABLE USERS("      \
      "ID INT PRIMARY KEY NOT NULL," \
      "NAME TEXT NOT NULL," \
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


void my_insert(char *sql){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ) 
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else 
      fprintf(stderr, "Opened database successfully\n");
     
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
}

void my_select(char *sql){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ) 
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else 
      fprintf(stderr, "Opened database successfully\n");   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback2, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}


static int check_if_user_exists(char *user){
  char *sql=malloc(strlen("SELECT NAME FROM USERS WHERE NAME = ")+strlen(user));

  strcat(sql,user);
  strcat(sql,"\n");
  printf("%s",sql);

  /* Open database */
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("test.db", &db);
   if( rc ) 
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else 
      fprintf(stderr, "Opened database successfully\n"); 

  //check for existance
  struct sqlite3_stmt *selectstmt;
  int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
  if(result == SQLITE_OK)
  {
     if (sqlite3_step(selectstmt) == SQLITE_ROW)
        return 1;
     else
        return 0;
  }
  sqlite3_finalize(selectstmt);

  free(sql);
  return 0;
}

int main(void) {
  

  puts("insert username:");
  char username[20];
  scanf("%s",username);
  printf("%s \n", username);

  // check_if_user_exists(username) ? my_insert(): puts()
  
  // char *sql = "INSERT INTO USERS (ID, NAME, IP, MAC)" \
  //       "VALUES (5,'MIHAI','SOMEIP','SOMEMAC')";

  // my_insert(sql);

  char *sql2 = "SELECT * FROM USERS WHERE NAME = 'MIHAI'";
  
  //my_select(sql2);
  printf("%d \n",check_if_user_exists(username));
  
  //create_table();
  //select2();
}















//creating database
  // char *zErrMsg = 0;
  // rc = sqlite3_open("test.db", &db);
   
  // if( rc ) {
  //    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  // }
  // else {
  //    fprintf(stderr, "Opened database successfully\n");
  // }