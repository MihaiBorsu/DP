#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>


int are_you_new_user(){
  puts("Are you new user? Y/N");
  char c = getchar();
  if (c == 'Y' || c == 'y')
    return 1;
  if (c == 'N' || c == 'n')
    return 0;
  return -1;
}

char *insert_username(){
  char *username;
  int n;
  puts("Insert username:");

  n = scanf("%ms", &username);
  if (n == 1){
    return username;
  }
  puts("Error scanning the username");
  return NULL;

}

char *insert_password(){
  char *password;
  int n;
  puts("Insert password:");

  n = scanf("%ms", &password);
  if (n == 1){
    return password;
  }
  puts("Error scanning the password");
  return NULL;
}

void check_host_name(int hostname) { //This function returns host name for local computer
   if (hostname == -1) {
      perror("gethostname");
      exit(1);
   }
}

void check_host_entry(struct hostent * hostentry) { //find host info from host name
   if (hostentry == NULL) {
      perror("gethostbyname");
      exit(1);
   }
}

char *retrive_ip(){
  char host[256];
  char *ip;
  struct hostent *host_entry;
  int hostname;

  hostname = gethostname(host, sizeof(host)); //find the host name
  check_host_name(hostname);
  host_entry = gethostbyname(host); //find host information
  check_host_entry(host_entry);
  ip = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
  return ip;
}

int check_username_existance(FILE *db,char *username){
  db = fopen("db.txt","r");
  char line[256];

  int i=0;
  while(fgets(line,sizeof(line),db)){
    if (i%4 == 0)
      if (strcmp(line,username) - '\n' == 0){
        fclose(db);
        return 1;
      }
    i++;
  }

  fclose(db);
  return 0;
}

int check_password(FILE *db,char *username,char *password){
  db = fopen("db.txt","r");
  char line[256];

  int i=0;
  while(fgets(line,sizeof(line),db)){
    if (i%4 == 0)
      if (strcmp(line,username) - '\n' == 0){
        fgets(line,sizeof(line),db);
        if (strcmp(line,password) - '\n' == 0){
          fclose(db);
          return 1;
        }
      }

    i++;
  }

  fclose(db);
  return 0;
}

void insert_to_database(FILE *db,char *username, char *password, char *ip){
  char *new_string = malloc(sizeof(char) * (strlen(username) + strlen(password) + strlen(ip) + 6));
  //new_string = "\0";

  strcat(new_string,username);
  strcat(new_string,"\n");
  strcat(new_string,password);
  strcat(new_string,"\n");
  strcat(new_string,ip);
  strcat(new_string,"\n");

  db = fopen("db.txt","a+");

  if (db == NULL){
    puts("Error opening the file pointer (insert_to_database function)");
    return;
  }

  fprintf(db, "%s\n", new_string);

  fclose(db);
  free(new_string);
}

void alter_ip(char *username, char *ip){
  db = fopen("db.txt","r");
  char line[256];

  int i=0;
  while(fgets(line,sizeof(line),db)){
    if (i%4 == 0)
      if (strcmp(line,username) - '\n' == 0){
        fclose(db);
        return 1;
      }
    i++;
  }

  fclose(db);
  return 0;
}


/*
Am gandit treaba în felul următor (așa e și în main-ul de mai jos comentat):
1) ești user nou?
DA:
  insert user
  insert pass
  retrive ip
  insert to database (it is a file we write in)
NU:
  insert user
  insert pass
  check user and pass
  retrive ip
  alter ip in the database
*/


// int main(void){
//   if are_you_new_user(){
//     username = insert_username();

//     while check_username_existance(username){
//       puts("username already exists, please try another username");
//       username = insert_username();
//     }

//     password = insert_password();
//     ip = retrive_ip();
//     insert_to_database(username,password,ip,mac);
//   }

//   else{
//     username = insert_username();
//     while !check_username_existance(username){
//       puts("username does not exists in the database, please try again.");
//       username = insert_username();
//     }

//     password = insert_password();
//     while !check_password(username,password){
//       puts("Wrong password, please try again");
//       password = insert_password();
//     }s

//     puts("You are now logged in");
//     ip = retrive_ip();

//     alter_ip_and_mac(username,ip,mac); //update with the new ip and mac
//   }

int main(int argc, char const *argv[]){
  /*printf("%d\n",are_you_new_user());
  char *username = insert_username();
  char *password = insert_password();
  char *ip = retrive_ip();*/

  FILE *db;
  //insert_to_database(db,username,password,ip);
  //printf("%d\n", check_username_existance(db,"Andreeaea"));
  printf("%d\n", check_password(db,"Mihai","G0585badcxz"));
  return 0;
}


