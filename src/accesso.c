#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "accesso_utente.h"
#include "controlli.h"
#include "menu_admin.h"

#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_NOME 50
#define MAX_COGNOME 50

// ADMIN O UTENTE
int accesso() {
  int accesso=0;
  int ris=0;
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];
  char nome[MAX_NOME], cognome[MAX_COGNOME];
  // SELEZIONE DEL TIPO DI ACCESSO
  while(accesso <= 0 || accesso >2)
  {
  printf("------------------------------------------------------\n");
  printf("Seleziona il tipo di accesso:\n");
  printf("1. Utente\n");
  printf("2. Amministratore\n");
  printf("------------------------------------------------------\n");
  scanf("%d", &accesso);
  }
  // PULIRE LA CRONOLOGIA DI ESECUZIONE
  switch (accesso) {
  case 1:
  while(ris <= 0 || ris >2)
  {
    printf("------------------------------------------------------\n");
    printf("1. Login\n");
    printf("2. Registrazione\n");
    printf("------------------------------------------------------\n");
    scanf("%d", &ris);
    }
    switch (ris) {
    case 1:
      login(username, password, nome, cognome);
      break;
    case 2:
      registrazione_utente();
      break;
    }
    break;
  case 2:
    printf("Inserisci l'username:\n");
    scanf("%s", username);
    // L'INSERIMENTO DELLA PASSWORD VERRA' OCCULTATA IN MODO DA AVERE UN MINIMO
    // DI PRIVACY
    printf("Inserisci la password:\n");
    scanf("%s", password);
    // RICHIAMO LA FUNZIONE PER L'AUTENTICAZIONE ALL'INTERNO DELL'IF DANDO ANCHE
    // I DATI INSERITI DA TASTIERA E SE ESSI SONO CORRETTI SI ACCEDE
    if (autenticazione(username, password)) {
      // Accesso come amministratore
      menu_admin();
      return 1;
    } else {
      // ALTRIMENTI L'UTENTE VERRA' SCOLLEGATO E PER RIACCEDERE DOVRA' RIAVVIARE
      // IL PROGRAMMA
      printf("Accesso negato, sto effettuando la disconnessione\n");
      system("cls");
      barra_di_caricamento_disconnessione();
      return 0;
    }
    break;
  }
  return 0;
}
