#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

/* portul folosit */

#define PORT 2728

extern int errno;		/* eroarea returnata de unele apeluri */


char tabla_joc[101][101], nrcopii;
int linie, coloana;
char matrice[101];
int x1, x2, piese_eliminate;
int z, y2;
/* functie de convertire a adresei IP a clientului in sir de caractere */
char * conv_addr (struct sockaddr_in address)
{
  static char str[25];
  char port[7];

  /* adresa IP a clientului */
  strcpy (str, inet_ntoa (address.sin_addr));	
  /* portul utilizat de client */
  bzero (port, 7);
  sprintf (port, ":%d", ntohs (address.sin_port));	
  strcat (str, port);
  return (str);
}

void desenare_tabla (){
    int cnt = 1;
    tabla_joc[0][0] = ' ';
    tabla_joc[0][1] = '|';
    for(coloana = 2; coloana <= 9; coloana++){
       tabla_joc[0][coloana] = cnt + '0';
       cnt++;
    } cnt = 1;
    for(coloana = 0; coloana <= 9; coloana++)
	tabla_joc[1][coloana] = '_';

    for(linie = 2; linie <= 9; linie++){
	tabla_joc[linie][0] = cnt + '0';
	tabla_joc[linie][1] = '|';
	cnt++;
	for(coloana = 2; coloana <= 9; coloana++)
	tabla_joc[linie][coloana] = 0 + '0'; //0 reprezinta loc pe tabla unde nu este nici o piesa
	tabla_joc[linie][10] = '\0';
    }

    for(linie = 2; linie <=9; linie++)
    tabla_joc[linie][2] = 1 + '0'; //1 reprezinta jucatorul alb
    for(coloana = 2; coloana <=8; coloana++)
    tabla_joc[9][coloana] = 1 + '0';
    
    for(coloana = 3; coloana <=9; coloana++)
    tabla_joc[2][coloana] = 2 + '0'; //2 reprezinta jucarorul negru
    for(linie = 2; linie <=9; linie++)
    tabla_joc[linie][9] = 2 + '0';

}

void matrice_in_sir(char tabla[101][101]){
    int cnt = 0;
    for(linie = 0; linie <= 9; linie++)
        for(coloana = 0; coloana <= 9; coloana++){
            matrice[cnt] = tabla[linie][coloana];
            cnt ++;
        }
    matrice[cnt] = '\0';
}

void sir_in_numere(char s[101]){

    x1 = s[0] - '0' + 1;
    x2 = s[1] - '0' + 1;
    z = s[3] - '0' + 1;
    y2 = s[4] - '0' + 1;

}

void mutare(char tabla[101][101], int x1, int x2, int z, int y2, int jucator){

    tabla[x1][x2] = 0 + '0';
    tabla[z][y2] = jucator + '0';

}

int mutare_imposibila(char tabla[101][101], int x1, int x2, int z, int y2, int jucator){
    if(x1 < 2 || x1 > 9 || x2 < 2 || x2 > 9 || z < 2 || z > 9 || y2 < 2 || y2 > 9) return 0;
    if(tabla[x1][x2] != (jucator + '0')) return 0;
    if(tabla[z][y2] != (0 + '0')) return 0;
    if(x1 != z && y2 != x2) return 0;
    if(x1 == z){
	if(y2 > x2){
    	for (coloana = x2+1; coloana <= y2; coloana ++)
    	    if (tabla[x1][coloana] != (0 + '0')) return 0;
	}
	else if(y2 < x2){
	    for (coloana = y2; coloana <= x2 - 1; coloana ++)
    	    if (tabla[x1][coloana] != (0 + '0')) return 0;
	}
	else return 0;
    }
    if(x2 == y2){
	if(z > x1){
            for (linie = x1+1; linie < z; linie ++)
    	    if (tabla[linie][x2] != (0 + '0')) return 0;
	}
	else if(z < x1){
            for (linie = z; linie <= x1 - 1; linie ++)
    	    if (tabla[linie][x2] != (0 + '0')) return 0;
	}
	else return 0;
    }
    return 1;
}

void elimina_piese(char tabla[101][101], int x1, int x2, int jucator1, int jucator2){

    int zero = 0, elimina = 0, cnt;
    if(tabla[x1][x2 - 1] == (jucator2 + '0') && x2 > 3){
        for(coloana = x2 - 1; coloana >= 2; coloana--){
            if(tabla[x1][coloana] == (0 + '0'))
                zero = 1;
            if(tabla[x1][coloana] == (jucator1 + '0') && zero == 0)
                elimina = 1;
        }
        if(elimina == 1){
            cnt = x2 - 1;
            while(tabla[x1][cnt] != (jucator1 + '0')){
                tabla[x1][cnt] = 0 + '0';
                cnt--;
                piese_eliminate++;
            }
        }
    }
    zero = 0;
    elimina = 0;
    if(tabla[x1][x2 + 1] == (jucator2 + '0') && x2 < 8){
        for(coloana = x2 + 1; coloana <= 9; coloana++){
            if(tabla[x1][coloana] == (0 + '0'))
                zero = 1;
            if(tabla[x1][coloana] == (jucator1 + '0') && zero == 0)
                elimina = 1;
        }
        if(elimina == 1){
            cnt = x2 + 1;
            while(tabla[x1][cnt] != (jucator1 + '0')){
                tabla[x1][cnt] = 0 + '0';
                cnt++;
                piese_eliminate++;
            }
        }
    }
    zero = 0;
    elimina = 0;
    if(tabla[x1 - 1][x2] == (jucator2 + '0') && x1 > 3){
        for(linie = x1 - 1; linie >= 2; linie--){
            if(tabla[linie][x2] == (0 + '0'))
                zero = 1;
            if(tabla[linie][x2] == (jucator1 + '0') && zero == 0)
                elimina = 1;
        }
        if(elimina == 1){
            cnt = x1 - 1;
            while(tabla[cnt][x2] != (jucator1 + '0')){
                tabla[cnt][x2] = 0 + '0';
                cnt--;
                piese_eliminate++;
            }
        }
    }
    zero = 0;
    elimina = 0;
    if(tabla[x1 + 1][x2] == (jucator2 + '0') && x1 < 8){
        for(linie = x1 + 1; linie <= 9; linie++){
            if(tabla[linie][x2] == (0 + '0'))
                zero = 1;
            if(tabla[linie][x2] == (jucator1 + '0') && zero == 0)
                elimina = 1;
        }
        if(elimina == 1){
            cnt = x1 + 1;
            while(tabla[cnt][x2] != (jucator1 + '0')){
                tabla[cnt][x2] = 0 + '0';
                cnt++;
                piese_eliminate++;
            }
        }
    }

}

int incheierejoc_jucatorblocat(char tabla[101][101], int numar){
    
    for(linie = 2; linie <= 9; linie++)
	for(coloana = 2; coloana <= 9; coloana++)
	if(tabla[linie][coloana] == (numar + '0'))
	    if(tabla[linie][coloana - 1] == (0 + '0') || tabla[linie][coloana + 1] == (0 + '0') || tabla[linie - 1][coloana] == (0 + '0') || tabla[linie + 1][coloana] == (0 + '0')){
		return 1; //exista o mutare posibila si jocul poate continua

	    }
    return 0; //jucatorul cu numarul "numar" nu mai poate face nici o mutare deci jocul s-a incheiat
    }

int inchieierejoc_jucator_fara_piese(char tabla[101][101], int numar){
    int piese = 0;
    for(linie = 2; linie <= 9; linie++)
	for(coloana = 2; coloana <=9; coloana++)
	if(tabla[linie][coloana] == (numar + '0')) piese++;

    if(piese <= 1) return 0; //jucatorul cu numarul "numar" nu mai are suficiente piese pentru a continua jocul
    return 1;
    }

void tabel_piese(int joc){
    FILE *tabel_piese;
    int nr_var = 1, info1, ok = 0;
    char info[101], ctabel[10001], piese_eliminates[101], linie[101], jocs[101];
    bzero(ctabel, 10001);
    sprintf(piese_eliminates, "%d", piese_eliminate);
    sprintf(jocs, "%d", joc);

    strcpy(linie, piese_eliminates);
    strcat(linie, " piese_eliminate joc ");
    strcat(linie, jocs);
    strcat(linie, "\n");

    tabel_piese = fopen("tabelp.txt", "r");

    while(!feof(tabel_piese)){
        
        fscanf(tabel_piese,"%s", info);
        if(nr_var % 4 == 1) {
            info1 = atoi(info);
            if(piese_eliminate > info1 && ok == 0){
                strcat(ctabel, linie);
                ok = 1;
            }
        }
        strcat(ctabel , info);
        if(nr_var % 4 != 0){
            strcat(ctabel, " ");
            }
        else{
            strcat(ctabel, "\n");
            }
        nr_var++;
    }
    fclose(tabel_piese);

    if(ok == 0){
        strcat(ctabel, linie);
    }

    ctabel[strlen(ctabel) - 1] = '\0';

    tabel_piese = fopen("tabelp.txt", "w");
    fprintf(tabel_piese, "%s", ctabel);
    fclose(tabel_piese);

}

void tabel_mutari(int mutari, int joc){

    FILE *tabel_mutari;
    int nr_var = 1, info1, ok = 0;
    char info[101], ctabel[10001], mutaris[101], linie[101], jocs[101];
    bzero(ctabel, 10001);
    sprintf(mutaris, "%d", mutari);
    sprintf(jocs, "%d", joc);

    strcpy(linie, mutaris);
    strcat(linie, " mutari joc ");
    strcat(linie, jocs);
    strcat(linie, "\n");

    tabel_mutari = fopen("tablem.txt", "r");

    while(!feof(tabel_mutari)){
        
        fscanf(tabel_mutari,"%s", info);
        if(nr_var % 4 == 1) {
            info1 = atoi(info);
            if(mutari > info1 && ok == 0){
                strcat(ctabel, linie);
                ok = 1;
            }
        }
        strcat(ctabel , info);
        if(nr_var % 4 != 0){
            strcat(ctabel, " ");
            }
        else{
            strcat(ctabel, "\n");
            }
        nr_var++;
    }
    fclose(tabel_mutari);

    if(ok == 0){
        strcat(ctabel, linie);
    }

    ctabel[strlen(ctabel) - 1] = '\0';

    tabel_mutari = fopen("tablem.txt", "w");
    fprintf(tabel_mutari, "%s", ctabel);
    fclose(tabel_mutari);

}


/* programul */
int main ()
{
  struct sockaddr_in server;	/* structurile pentru server si clienti */
  struct sockaddr_in from;
  fd_set readfds;		/* multimea descriptorilor de citire */
  fd_set actfds;		/* multimea descriptorilor activi */
  struct timeval tv;		/* structura de timp pentru select() */
  int sd, client;		/* descriptori de socket */
  int optval=1; 			/* optiune folosita pentru setsockopt()*/ 
  int fd;			/* descriptor folosit pentru 
       parcurgerea listelor de descriptori */
  int nfds;			/* numarul maxim de descriptori */
  int len;			/* lungimea structurii sockaddr_in */
  int nrclienti = 0, nusejoaca = 0, conectati[100001], client1, client2, castigator = 0;
  int pfd[2];
  char password[101], nume[50], info[50];
  char *name, name1[101];
  char *command, *p, rasp[101], raspuns[101], raspuns_tata[101];
  FILE *user_file;
  char user_data[1000001];
  int joc = 0, joc1, joc2;

  /* creare socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server] Eroare la socket().\n");
      return errno;
    }

  /*setam pentru socket optiunea SO_REUSEADDR */ 
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));

  /* pregatim structurile de date */
  bzero (&server, sizeof (server));

  /* umplem structura folosita de server */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl (INADDR_ANY);
  server.sin_port = htons (PORT);

  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server] Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 5) == -1)
    {
      perror ("[server] Eroare la listen().\n");
      return errno;
    }
  
  /* completam multimea de descriptori de citire */
  FD_ZERO (&actfds);		/* initial, multimea este vida */
  FD_SET (sd, &actfds);		/* includem in multime socketul creat */

  tv.tv_sec = 1;		/* se va astepta un timp de 1 sec. */
  tv.tv_usec = 0;
  
  /* valoarea maxima a descriptorilor folositi */
  nfds = sd;

  printf ("[server] Asteptam la portul %d...\n", PORT);
  fflush (stdout);
        
  /* servim in mod concurent clientii... */
  while (1)
    {
      /* ajustam multimea descriptorilor activi (efectiv utilizati) */
      bcopy ((char *) &actfds, (char *) &readfds, sizeof (readfds));

      /* apelul select() */
      if (select (nfds+1, &readfds, NULL, NULL, &tv) < 0)
	{
      perror ("[server] Eroare la select().\n");
      return errno;
	}
      /* vedem daca e pregatit socketul pentru a-i accepta pe clienti */
      if (FD_ISSET (sd, &readfds))
	{
      /* pregatirea structurii client */
      len = sizeof (from);
      bzero (&from, sizeof (from));

      /* a venit un client, acceptam conexiunea */
      client = accept (sd, (struct sockaddr *) &from, &len);

      /* eroare la acceptarea conexiunii de la un client */
      if (client < 0)
        {
          perror ("[server] Eroare la accept().\n");
          continue;
        }

      if (nfds < client) /* ajusteaza valoarea maximului */
        nfds = client;
            
      /* includem in lista de descriptori activi si acest socket */
      FD_SET (client, &actfds);

      printf("[server] S-a conectat clientul cu descriptorul %d, de la adresa %s.\n",client, conv_addr (from));
      fflush (stdout);
	}
      /* vedem daca e pregatit vreun socket client pentru a trimite raspunsul */
      for (fd = 0; fd <= nfds; fd++)	/* parcurgem multimea de descriptori */
	{
      /* este un socket de citire pregatit? */
      if ((fd != sd && FD_ISSET (fd, &readfds)))
        {	
          int pid, i, nr, nr2;
          int conectat = 0;

          if ((pid = fork()) == -1){
            perror("Eroare la fork!\n");
            continue;
          }
          
          else if (pid == 0){
            while(conectat == 0){
                char msg[101], msgrasp[101];
                nr = 0;
                nr2 = 0;
                int bte = 0;
                bzero (msg, 100);
                if ((bte = read (fd, msg, sizeof(msg))) <= 0){
                    perror("Eroare la read() de la client.\n");
                    continue;
                    }
                fflush (stdout);
                printf ("[server]Mesajul a fost receptionat...%s, %d\n", msg, bte);
                for(i = 1; i <= strlen(msg) - 1; i++){
                    if(msg[i] == ' '){
                        nr++;
                    }
                    else if(msg[i] == ':'){
                        nr2++;
                    }
                }
                if(nr != 1 || nr2 != 2 ){
                    strcpy(rasp, "Nu ati scris corect comanda. Incercati din nou!\n");
                }

                else if ((strstr(msg, "user:")) && (strstr(msg, "password:"))){

                    command = strtok(msg, " ");
                    strcpy(name1, command);
                    command = strtok(NULL, " ");
                    strcpy(password, command);
                    name = strtok(name1, ":");
                    name = strtok(NULL, ":");
                    p = strtok(password, ":");
                    p = strtok(NULL, ":");
                    strcpy(password, p);
                    strcpy(name1, name);
                    int nr_var = 1;
                    user_file = fopen("user.txt", "r");
                    while(!feof(user_file)){
                    
                    fscanf(user_file,"%s", info);
                    strcat(user_data, info);
                    if(nr_var % 2 != 0){
                        strcat(user_data, " ");
                        }
                    else{
                        strcat(user_data, "\n");
                        }
                    nr_var++;
                    }
                    
                    //strcpy(user_data+strlen(user_data)-strlen(info)-1, user_data+strlen(user_data));
                    fclose(user_file);
                    strcat(user_data, name1);
                    strcat(user_data, " ");
                    strcat(user_data, password);
                    user_data[strlen(user_data) - 1] = '\0';
                    user_file = fopen("user.txt", "w");
                    fprintf(user_file,"%s", user_data);
                    fclose(user_file);
                    strcpy(rasp, "conectat\n");
                    conectat = 1;
                }
                else if ((strstr(msg, "login:")) && (strstr(msg, "password:"))){
                    command = strtok(msg, " ");
                    strcpy(name1, command);
                    command = strtok(NULL, " ");
                    strcpy(password, command);
                    name = strtok(name1, ":");
                    name = strtok(NULL, ":");
                    p = strtok(password, ":");
                    p = strtok(NULL, ":");
                    strcpy(password, p);
                    strcpy(name1, name);
                    password[strlen(password) - 1] = '\0';
                    user_file = fopen("user.txt", "r");
                    while(!feof(user_file)){
                                
                        bzero(nume, sizeof(nume));
                        fscanf(user_file,"%s", nume);
                            
                        if(strcmp(nume, name1) == 0)
                        {
                                        char password1[50];
                                        
                            fscanf(user_file, "%s", password1);
                            
                            if(strcmp(password, password1) == 0){
                            strcpy(rasp, "conectat\n");
                            
                            conectat = 1;
                            break;
                            }
                            else {
                            strcpy(rasp, "parola gresita. incearca din nou\n");
                            break;
                            }
                        }
                        else strcpy(rasp, "utilizator negasit. incearca din nou\n");
                        
                        
                            
                        }
                    fclose(user_file);
                    }
                else{
                    strcpy(rasp, "Nu ati scris corect comanda. Incercati din nou!\n");
                }
                bzero(msgrasp,100);
                strcpy(msgrasp, rasp);
                
                if (write (fd, msgrasp, 100) <= 0)
                    {
                    perror ("[server]Eroare la write() catre client.\n");
                    continue;		/* continuam sa ascultam */
                    }
                else
                    printf ("[server]Mesajul a fost trasmis cu succes.\n");
                
                    
                
                    } 
            exit(2);
    	}
    	else if (pid > 0){
    	    wait(NULL);
            nrclienti++;
            
            conectati[nrclienti] = fd;
    	    if(nrclienti%2 == 1)
    		nusejoaca = 1;
    	    
    	    }
    	
        }
      }			/* for */
	
        if(nrclienti%2 == 0 && nrclienti != 0 && nusejoaca == 1){
            
            printf("joc pornit\n");
            nusejoaca = 0;
            joc++;
            int ppid;
            joc2 = 0;
            client2 = conectati[nrclienti];
            client1 = conectati[nrclienti-1];
            if ((ppid = fork()) == -1){
                perror("Eroare la fork!\n");
                continue;
            }
            
            else if (ppid == 0){
                while(1){
                    int bte, jucator, mutare_corecta;
                    char msg[101];
                    int ok;
                    if(joc2%10 == 9){
                        joc*=10;
                    }
                    joc1 = joc*10 + joc2;
                    ok = 0;
                    
                    char msgrasp[10001];
                    bzero(msgrasp,10000);
                    
                    strcpy(msgrasp, "Jocul a inceput!\n REGULI JOC: Puteti muta doar pe linie sau coloana, oricate spatii doriti, asemenea unui turn din \"sah\".\n         Nu puteti muta peste o alta piesa, puteti muta doar cat aveti spatii libere.\n         Pentru a elimina o piesa puteti muta o piesa langa piesa unui alt jucator, iar piesa celuilalt jucator va fii eliminata daca in partea cealalta a piesei aveti alt pion. Ex: (va fii eliminata piesa/piesele jutaroului 1) \"212\" sau \"2112\" si asa mai departe. Oricate piese se afla intre piesele jucatorului curent vor fii eliminate.\n         Vor fii eliminate doar piesele blocate de mutarea curenta.\n Veti observa ca tabla jocului este bordata in partea stanga si in partea superioara pentru a putea cunoaste pozitiile pieselor.\n\n Sunteti jucatorul cu numarul 1 si veti incepe!\n");
                    if (write (client1, msgrasp, 10000) <= 0)
                            {
                        perror ("[server]Eroare la write() catre client.\n");
                        continue;		/* continuam sa ascultam */
                            }
                    else
                        printf ("[server]Mesajul a fost trasmis cu succes.\n");
                    bzero(msgrasp, 10000);
                    strcpy(msgrasp, "Jocul a inceput!\n REGULI JOC: Puteti muta doar pe linie sau coloana, oricate spatii doriti, asemenea unui turn din \"sah\".\n         Nu puteti muta peste o alta piesa, puteti muta doar cat aveti spatii libere.\n         Pentru a elimina o piesa puteti muta o piesa langa piesa unui alt jucator, iar piesa celuilalt jucator va fii eliminata daca in partea cealalta a piesei aveti alt pion. Ex: (va fii eliminata piesa/piesele jutaroului 1) \"212\" sau \"2112\" si asa mai departe. Oricate piese se afla intre piesele jucatorului curent vor fii eliminate.\n         Vor fii eliminate doar piesele blocate de mutarea curenta.\n Veti observa ca tabla jocului este bordata in partea stanga si in partea superioara pentru a putea cunoaste pozitiile pieselor.\n\n Sunteti jucatorul cu numarul 2. Va incepe jucatorul cu numarul 1.\n");
                    if (write (client2, msgrasp, 10000) <= 0)
                                {
                            perror ("[server]Eroare la write() catre client.\n");
                            continue;		/* continuam sa ascultam */
                                }
                        else
                            printf ("[server]Mesajul a fost trasmis cu succes.\n");
                    desenare_tabla();
                    int nr_mutari = 0;
                    piese_eliminate = 0;
                    while(ok == 0){
                        while(1)
                        {
                        
                            jucator = 1;
                            mutare_corecta = 0;
                            bzero(msgrasp, 10000);
                            matrice_in_sir(tabla_joc);
                            strcpy(msgrasp, matrice);
                            
                            if (write (client1, msgrasp, 10000) <= 0)
                            {
                                perror ("[server]Eroare la write() catre client.\n");
                                continue;		/* continuam sa ascultam */
                            }
                            else
                                printf ("[server]Mesajul a fost trasmis cu succes.\n");
                            while(mutare_corecta == 0){
                                bzero (msg, 100);
                                if ((bte = read (client1, msg, sizeof(msg))) <= 0){
                                    perror("Eroare la read() de la client.\n");
                                    continue;
                                }
                                fflush (stdout);
                                printf ("[server]Mesajul a fost receptionat3...%s, %d\n", msg, bte);
                                if(strcmp(msg, "incheie joc") == 0) {
                                    printf("jucator 1 a incheiet\n");
                                    mutare_corecta = 1;
                                    break;
                                }
                                sir_in_numere(msg);
                                if (mutare_imposibila(tabla_joc, x1, x2, z, y2, jucator)){
                                    mutare_corecta = 1;
                                }
                                else {
                                    strcpy(msgrasp, "Mutare gresita. Incearca din nou!\n");
                                    if (write (client1, msgrasp, 10000) <= 0)
                                    {
                                        perror ("[server]Eroare la write() catre client.\n");
                                        continue;		/* continuam sa ascultam */
                                    }
                                    else
                                        printf ("[server]Mesajul a fost trasmis cu succes.\n");
                                }
                            }
                            if(strcmp(msg, "incheie joc") == 0){
                                castigator = 2;
                                printf("castiga 2\n");
                                break;
                            }
                            mutare(tabla_joc, x1, x2, z, y2, jucator);
                            nr_mutari++;
                            elimina_piese(tabla_joc, z, y2, 1, 2);
                            bzero(msgrasp, 10000);
                            strcpy(msgrasp, "S-a realizat mutarea\n");
                            if (write (client1, msgrasp, 10000) <= 0)
                            {
                                perror ("[server]Eroare la write() catre client.\n");
                                continue;		/* continuam sa ascultam */
                            }
                            else
                                printf ("[server]Mesajul a fost trasmis cu succes.\n");

                            if(incheierejoc_jucatorblocat(tabla_joc, 2) == 0 || inchieierejoc_jucator_fara_piese(tabla_joc, 2) == 0)
                                {
                                    castigator = 1;
                                    break;
                                }

                            //client2
                            jucator = 2;
                            mutare_corecta = 0;
                            bzero(msgrasp, 10000);
                            matrice_in_sir(tabla_joc);
                            //printf("%s", matrice);
                            strcpy(msgrasp, matrice);
                            

                            if (write (client2, msgrasp, 10000) <= 0)
                            {
                                perror ("[server]Eroare la write() catre client.\n");
                                continue;		/* continuam sa ascultam */
                            }
                            else
                                printf ("[server]Mesajul a fost trasmis cu succes.\n");
                        
                            while(mutare_corecta == 0){
                                bzero (msg, 100);
                                if ((bte = read (client2, msg, sizeof(msg))) <= 0){
                                    perror("Eroare la read() de la client.\n");
                                    continue;
                                }
                                fflush (stdout);
                                printf ("[server]Mesajul a fost receptionat2...%s, %d\n", msg, bte);
                                if(strcmp(msg, "incheie joc") == 0){
                                    mutare_corecta = 1;
                                    printf("jucator 2 a incheiat.\n");
                                    break;
                                }
                                sir_in_numere(msg);
                                if (mutare_imposibila(tabla_joc, x1, x2, z, y2, jucator))
                                    mutare_corecta = 1;
                                else {
                                    strcpy(msgrasp, "Mutare gresita. Incearca din nou!\n");
                                    if (write (client2, msgrasp, 10000) <= 0)
                                            {
                                        perror ("[server]Eroare la write() catre client.\n");
                                        continue;		/* continuam sa ascultam */
                                            }
                                    else
                                        printf ("[server]Mesajul a fost trasmis cu succes.\n");
                                }
                                        
                            }
                            if(strcmp(msg, "incheie joc") == 0){
                                castigator = 1;
                                printf("castiga jucator 1");
                                break;
                            }
                            mutare(tabla_joc, x1, x2, z, y2, jucator);
                            nr_mutari++;
                            elimina_piese(tabla_joc, z, y2, 2, 1);
                            bzero(msgrasp, 10000);
                            strcpy(msgrasp, "S-a realizat mutarea");
                            if (write (client2, msgrasp, 10000) <= 0)
                            {
                                perror ("[server]Eroare la write() catre client.\n");
                                continue;		/* continuam sa ascultam */
                            }
                            else
                                printf ("[server]Mesajul a fost trasmis cu succes.\n");

                            if(incheierejoc_jucatorblocat(tabla_joc, 1) == 0 || inchieierejoc_jucator_fara_piese(tabla_joc, 1) == 0)
                            {
                                castigator = 2;
                                break;
                            }

                        }
                
                        tabel_mutari(nr_mutari, joc1);
                        tabel_piese(joc1);
                        bzero(msgrasp, 10000);
                        strcpy(msgrasp, "Joc incheiat. A castigat jucatorul ");
                        msgrasp[35] = castigator + '0';
                        if (write (client1, msgrasp, 10000) <= 0)
                        {
                            perror ("[server]Eroare la write() catre client.\n");
                            continue;		/* continuam sa ascultam */
                        }
                            else
                                printf ("[server]Mesajul a fost trasmis cu succes.\n");
                        
                        if (write (client2, msgrasp, 10000) <= 0)
                            {
                                perror ("[server]Eroare la write() catre client.\n");
                                continue;		/* continuam sa ascultam */
                            }
                        else
                            printf ("[server]Mesajul a fost trasmis cu succes.\n");

                        bzero (msg, 100);
                        if ((bte = read (client1, msg, sizeof(msg))) <= 0){
                            perror("Eroare la read() de la client.\n");
                            continue;
                        }


                        fflush (stdout);
                        printf ("[server]Mesajul a fost receptionat in afara while...%s, %d\n", msg, bte);

                        bzero (msg, 100);
                        if ((bte = read (client2, msg, sizeof(msg))) <= 0){
                            perror("Eroare la read() de la client.\n");
                            continue;
                        }

                        fflush (stdout);
                        printf ("[server]Mesajul a fost receptionat client 2...%s, %d\n", msg, bte);
                        joc2++;
                        ok = 1;
                    }
                }
            }
	    }
    }				/* while */
}				/* main */