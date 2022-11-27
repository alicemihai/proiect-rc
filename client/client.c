/* cliTCPIt.c - Exemplu de client TCP
   Trimite un nume la server; primeste de la server "Hello nume".
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

  int sd; // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare 
  char msg[100]; // mesajul trimis
  char user[50]; //numele de utilizator

int send_message(int type)
{
    /* cream socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("Eroare la socket().\n");
      return errno;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;

    /* portul de conectare */
    server.sin_port = htons(port);

    /* ne conectam la server */
    if (connect(sd, (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) {
      perror("[client]Eroare la connect().\n");
      return errno;
    }

if(type==0)
{
      /* citirea mesajului */
    bzero(msg, 100);
    printf("[%s]: ",user);
    fflush(stdout);
    read(0, msg, 100);
    char msg2[100];
    bzero(msg2, 100);
    if(strncmp(msg, "clear-history",13)!=0)
    {
      strcat(msg2, user);
    strcat(msg2, ": ");
    }
    
    strcat(msg2, msg);
    
    /* trimiterea mesajului la server */
    if (write(sd, msg2, 100) <= 0) {
      perror("[client]Eroare la write() spre server.\n");
      return errno;
    }
}
else if(type==1)
{
      /* citirea mesajului */
    strcpy(msg, "get-history");

    /* trimiterea mesajului la server */
    if (write(sd, msg, 100) <= 0) {
      perror("[client]Eroare la write() spre server.\n");
      return errno;
    }
}
    /* citirea raspunsului dat de server 
       (apel blocant pina cind serverul raspunde); Atentie si la cum se face read- vezi cursul! */
    if (read(sd, msg, 100) < 0) {
      perror("[client]Eroare la read() de la server.\n");
      return errno;
    }
    /* afisam mesajul primit */
    printf("[client]Mesajul primit este: %s\n", msg);

    /* inchidem conexiunea, am terminat */
    close(sd);
    return 0;
}

int main(int argc, char * argv[]) {

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3) {
    printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(argv[1]);

     bzero(user, 50);
    printf("[client]Introduceti utilizatorul: ");
    fflush(stdout);
    read(0, user, 50);
    user[strlen(user)-1]=0;
  /* stabilim portul */
  port = atoi(argv[2]);
send_message(1);

  while (1 == 1) {
    send_message(0);
  }
}