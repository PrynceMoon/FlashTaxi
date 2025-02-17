#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "dati.h"
#include "controlli.h"
#include "menu_utente.h"

// REGISTRAZIONE AL PROGRAMMA SE L'UTENTE NON NE HA MAI EFFETTUATA UNA
void registrazione_utente() {
  FILE* fp = fopen("utenti.bin", "ab+");
  if (fp == NULL) {
	  printf("Errore durante l'apertura del file.\n");
  }else{

    printf("Inserisci il tuo nome: ");
    scanf("%s", r.reg_nome);
    r.reg_nome[strcspn(r.reg_nome, "\n")] = '\0';
    while (controllo(r.reg_nome)) {
      printf("Nome non valido, riprova: ");
      scanf("%s", r.reg_nome);
    }
    printf("Inserisci il tuo cognome: ");
    scanf("%s", r.reg_cognome);
    r.reg_cognome[strcspn(r.reg_cognome, "\n")] = '\0';
    while (controllo(r.reg_cognome)) {
      printf("Cognome non valido, riprova: ");
      scanf("%s", r.reg_cognome);
    }
    printf("Inserisci il tuo username: ");
    scanf("%s", r.username);
    r.username[strcspn(r.username, "\n")] = '\0';
    while (controllo(r.username)) {
      printf("Username non valido, riprova: ");
      scanf("%s", r.username);
    }
    printf("Inserisci la tua password: ");
    scanf("%s", r.password);
    r.password[strcspn(r.password, "\n")] = '\0';
    // SCRIVERE ALL'INTERNO DEL FILE I DATI PRESENTI NELLA STRUTTURA DATI
    fwrite(&r, sizeof(r), 1, fp);
    // CHIUSURA DEL FILE
    fclose(fp);

    // TERMINATA LA REGISTRAZIONE L'UTENTE VIENE RINDIRIZZATO AL MENU' UTENTE
    menu_utente(r.reg_nome, r.reg_cognome);
  }
}

int login(char nome[], char cognome[], char username[], char password[]) {
  int login_success = 0;
  // APERTURA DEL FILE CONTENENTE I DATI D'ACCESSO DEI VARI UTENTI
  FILE* fp = fopen("utenti.bin", "rb");
  if (fp == NULL) {
    printf("Errore durante l'apertura del file.\n");
  } else {
    printf("Username: ");
    scanf("%s", username);
    while (controllo(username)) {
      printf("Username non valido, riprova: ");
      scanf("%s", username);
    }
    printf("Password: ");
    scanf("%s", password);
    // Rimuovi il carattere di nuova riga (\n) inserito alla fine della stringa
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';
    // LETTURA DEI DATI D'ACCESSO PRESENTI NEL FILE
    fread(&r, sizeof(struct Registrazione), 1, fp);
    while (!feof(fp)) {
      // CONFRONTO I DATI D'ACCESSO PRESENTI NEL FILE CON QUELLI INSERITI DA TASTIERA
      if (strcmp(r.username, username) == 0 &&
          strcmp(r.password, password) == 0) {
        printf("Accesso riuscito.\n");
        login_success = 1;
        strcpy(nome, r.reg_nome);
        strcpy(cognome, r.reg_cognome);
        menu_utente(nome, cognome);
        break;
      }
      fread(&r, sizeof(struct Registrazione), 1, fp);
    }
    // CHIUSURA DEL FILE QUANDO VIENE EFFETTUATO L'ACCESSO
    fclose(fp);
    // MESSAGGIO DI ERRORE QUANDO LE CREDENZIALI SONO SBAGLIATE
    if (!login_success) {
      printf("\nAccesso fallito. Controlla username e password.\n");
      return 0;
    }
  }
  return 0;
}

