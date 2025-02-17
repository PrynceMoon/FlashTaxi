#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "dati.h"
#include "funzioni_utente.h"
#include "stampa_viaggi.h"

// MENU' LATO UTENTE IN CUI ESSO DOVRA' SELEZIONARE I COMANDI DA EFFETTUARE
void menu_utente(char n[], char c[]) {
  int assegnazioneU = 0;
  int U = 1;
  float val=0;
  char cvs[MAX_COD_VIAGGIO];
  char input[3];
  while (U == 1) {
    while (assegnazioneU <= 0 || assegnazioneU >3) {
      printf("------------------------------------------------------\n");
      printf("Benvenuto, %s %s!\n", n, c);
      printf("1. Effettua Prenotazione\n");
      printf("2. Guidatore con maggior valutazione\n");
      printf("3. Esci\n");
      printf("------------------------------------------------------\n");

      while (getchar() != '\n') {
        // Svuota il buffer di input
      }


      fgets(input, sizeof(input), stdin);
     	      // Conversione dell'input in un numero intero
     	      char *endptr;
     	      assegnazioneU = strtol(input, &endptr, 10);
     	      // Controllo se la conversione ha avuto successo e se il numero è compreso tra 1 e 5
     	      if (endptr == input || *endptr != '\n' || assegnazioneU < 1 || assegnazioneU > 3) {
     	        printf("Hai inserito un valore non valido. Riprova.\n");
     	        assegnazioneU = 0;
     	      }
    }

    switch (assegnazioneU) {
    case 1:
      prenotazione(n, c, cvs, val);
      assegnazioneU = 0;
      break;
    case 2:
      stampa_guidatore_valutazione_massima();
      assegnazioneU = 0;
      break;
    case 3:
      U = 0;
      break;
    default:
      printf("Opzione non valida\n");
      assegnazioneU = 0;
      break;
    }
  }
}
