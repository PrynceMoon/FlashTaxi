#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// DEFINISCO LE VARIABILI PER L'ACCESSO LATO ADMIN
#define USERNAME "admin"
#define PASSWORD "password"

// CONTROLLO CARATTERI
int controllo(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            return 1; // Restituisce 1 se trova un carattere numerico
        }
        i++;
    }
    return 0; // Restituisce 0 se non trova caratteri numerici
}

// FUNZIONE CHE CONFERMA L'ACCESSO AL LATO ADMIN
int autenticazione(const char *username, const char *password) {
  // VERIFICA DEI DATI INSERITI CON I DATI IMPOSTATI PRECEDENTEMENTE
  if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
    // I DATI SONO CORRETTI E L'UTENTE ACCEDE AL LATO ADMIN
    return 1;
  }
  // I DATI INSERITI NON SONO CORRETTI E L'UTENTE VIENE SCOLLEGATO
  return 0;
}


// BARRA DI CARICAMENTO DELLA DISCONNESSIONE
void barra_di_caricamento_disconnessione() {
	int i;
	  printf("Sto effettuando la disconnessione: [");

	  for (i = 0; i <= 50; i++) {
	    printf("=");
	    fflush(stdout); // Flusso di output forzato per visualizzare subito la barra di avanzamento
	    usleep(200000);
	  }

	  printf("]\nDisconnessione effettuata con successo\n");
	}



// BARRA DI CARICAMENTO DELLA PRENOTAZIONE
void barra_di_caricamento_accettazioneviaggio() {
  int i;
    printf("Sto effettuando la prenotazione: [");

   	  for (i = 0; i <= 50; i++) {
   	    printf("=");
   	    fflush(stdout); // Flusso di output forzato per visualizzare subito la barra di avanzamento
   	    usleep(200000);
   	  }
  printf("]\nPrenotazione effettuata con successo\n");
}


// BARRA DI CARICAMENTO DELLA SIMULAZIONE DEL VIAGGIO
void barra_di_caricamento_simulazioneviaggio() {
  int i;
    printf("Sto effettuando la corsa: [");


   	  for (i = 0; i <= 50; i++) {
   	    printf("=");
   	    fflush(stdout); // Flusso di output forzato per visualizzare subito la barra di avanzamento
   	    usleep(200000);
   	  }
  printf("]\nSiamo arrivati a destinazione\n");
}
int controlli_data(int mese, int giorno) {
	while (mese <= 0 || mese > 12) {
	    printf("Mese errato, riprova: ");
	    scanf("%d", &mese);
	    if (mese == 1) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Giorno errato, riprova: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 2) {
	      while (giorno <= 0 || giorno > 29) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 3) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 4) {
	      while (giorno <= 0 || giorno > 30) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 5) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 6) {
	      while (giorno <= 0 || giorno > 30) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 7) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 8) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 9) {
	      while (giorno <= 0 || giorno > 30) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 10) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 11) {
	      while (giorno <= 0 || giorno > 30) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    } else if (mese == 12) {
	      while (giorno <= 0 || giorno > 31) {
	        printf("Inserisci il giorno: ");
	        scanf("%d", &giorno);
	      }
	    }
	  }
	  return giorno;
}

