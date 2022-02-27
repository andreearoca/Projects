#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;
char tabla[101][101];
int linie, coloana;


void sir_in_matrice(char msgrasp[1001]){
    int cnt = 0;
    for(linie = 0; linie <= 9; linie++)
        for(coloana = 0; coloana <= 9; coloana++){
            tabla[linie][coloana] = msgrasp[cnt];
            cnt ++;
        }
    msgrasp[cnt] = '\0';
      
}

int main (int argc, char *argv[])
{
  int sd, conectat = 0;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char msg[100000], msgrasp[100001];		// mesajul trimis
  int rand = 1;

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
  
  else printf ("[client]Pentru login scrieti: \"login:\'nume\' password:\'parola\'\" \n Pentru utilizator nou scireti:\"user:\'nume\' password:\'parola\'\". FARA SPATII.\n");
  while (conectat == 0){
    /* citirea mesajului */
    
    bzero (msg, 100);
    int bte = 0;
    fflush (stdout);
    read (0, msg, 100);
    /* trimiterea mesajului la server */
    if (write (sd, msg, 100) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
      }
      //printf("\n%d\n", bte);

    /* citirea raspunsului dat de server 
       (apel blocant pina cind serverul raspunde) */
      bzero(msgrasp, 100);
    if (read (sd, msgrasp, 100) < 0)
      {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
      }
    /* afisam mesajul primit */
    system("clear");
    printf ("%s\n", msgrasp);
    if (strstr(msgrasp, "conectat")) conectat = 1;
    
  }
  //conectat = 0;
  while(conectat == 1){
    
    printf(" Va rog asteptati conectarea unui nou client pentru a incepe jocul!\n");
    bzero(msgrasp, 10000);
    if (read (sd, msgrasp, 10000) < 0)
        {
          perror ("[client]Eroare la read() de la server.\n");
          return errno;
        }
    
    printf ("%s\n", msgrasp);
    int se_joaca = 1;
    while(se_joaca == 1){
      
      int comanda_corecta = 0;
      bzero(msgrasp, 100000);
      if (read (sd, msgrasp, 100000) < 0)
      {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
      }
      else if(strstr(msgrasp, "Joc incheiat. A castigat jucatorul ")){
        printf("%s\n", msgrasp);
        se_joaca = 0;
        break;
      }
      else {
        printf("Pentru a muta o piesa veti tasta mai intai pozitia piesei pe care vreti sa o mutati urmata de pozitia in care vreti sa o mutati. Spre ex pentru piesa din colt stanga sus daca vrem sa o mutam cu doua spatii mai jos vom tasta \"11 31\". Mai intai linia si apoi coloana.\n");
      }
      
      sir_in_matrice(msgrasp);
      
      for(int i = 0; i <= 9; i++){
        for(int j = 0; j <= 9; j++)
          printf("%c ",tabla[i][j]);
        printf("\n");
      }

      do{
        while(comanda_corecta == 0){
            bzero (msg, 100);
            fflush (stdout);
            read (0, msg, 100);
            msg[strlen(msg)-1] = '\0';

            if(strcmp(msg, "incheie joc") == 0) 
              break;
            if(strlen(msg) == 5){
                if(isdigit(msg[0]) && isdigit(msg[1]) && (msg[2] == ' ') && isdigit(msg[3]) && isdigit(msg[4])){
                  comanda_corecta = 1;
                }
                else printf("Comanda gresita. Tastati din nou comanda.\n");
              }
            else printf("Comanda gresita. Tastati din nou comanda.\n");
        }
        if(strcmp(msg, "incheie joc") == 0) 
              break;
        if (write (sd, msg, 100) <= 0)
        {
          perror ("[client]Eroare la write() spre server.\n");
          return errno;
        }

        bzero(msgrasp, 100000);

        if (read (sd, msgrasp, 100000) < 0)
        {
          perror ("[client]Eroare la read() de la server.\n");
          return errno;
        }

        printf("%s\n", msgrasp);
        comanda_corecta = 0;

      }while(strcmp(msgrasp, "Mutare gresita. Incearca din nou!\n") == 0 && se_joaca == 1);

      if(strcmp(msg, "incheie joc") == 0){
        if (write (sd, msg, 100) <= 0){
          perror ("[client]Eroare la write() spre server.\n");
          return errno;
        }
      }
    }
    
    printf("Pentru a incepe alt joc apasati orice.\n");
    fflush (stdout);

    bzero (msg, 100);
    read (0, msg, 100);
    msg[strlen(msg) - 1] = '\0';
   
    if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

    

  }
  
  
}