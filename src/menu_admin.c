#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "funzioni_admin.h"
#include "stampa_viaggi.h"

// MENU' LATO ADMIN IN CUI ESSO DOVRA' SELEZIONARE I COMANDI DA EFFETTUARE
void menu_admin() {
  int assegnazioneA = 0;
  int A = 1;
  char input[4];

  while (A == 1) {
    while (assegnazioneA <= 0 || assegnazioneA > 5) {
      printf("------------------------------------------------------\n");
      printf("Benvenuto amministratore!\n");
      printf("1. Aggiunta Viaggio\n");
      printf("2. Modifica Viaggio\n");
      printf("3. Rimuovi Viaggio\n");
      printf("4. Cronologia\n");
      printf("5. Esci\n");
      printf("------------------------------------------------------\n");

      while (getchar() != '\n') {
              // Svuota il buffer di input
            }

      fgets(input, sizeof(input), stdin);
      // Rimuovi il carattere di nuova riga inserito da fgets
      input[strcspn(input, "\n")] = '\0';

      // Conversione dell'input in un numero intero
      char *endptr;
      assegnazioneA = strtol(input, &endptr, 10);

      // Controllo se la conversione ha avuto successo e se il numero è compreso tra 1 e 5
      if (endptr == input || *endptr != '\0' || assegnazioneA < 1 || assegnazioneA > 5) {
        printf("Hai inserito un valore non valido. Riprova.\n");
        assegnazioneA = 0;
      }
    }

    switch (assegnazioneA) {
      case 1:
        aggiunta_viaggio();
        assegnazioneA=0;
        break;

      case 2:
        modifica_viaggio();
        assegnazioneA=0;
        break;

      case 3:
        rimuovi_viaggio();
        assegnazioneA=0;
        break;

      case 4:
        cronologia();
        assegnazioneA = 0;
        break;

      case 5:
        A = 0;
        break;
    }
  }
}

