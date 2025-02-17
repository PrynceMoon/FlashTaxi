#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "controlli.h"
#include "dati.h"
#include "stampa_viaggi.h"

// INIZIALIZZAZIONE DEI CAMPI DELLA STRUCT
void inizializzaGuid()
{
  conducente.corsa.posti_disp=0;
  conducente.corsa.costo=0;
  conducente.data.giorno=0;
  conducente.data.mese=0;
  conducente.data.anno=0;
}
// ACQUISIZIONE DEI DATI DEL GUIDATORE
void acquisizione_dati_guid()
{
  int valido;
  printf("Inserisci il nome guidatore: ");
  scanf("%s", conducente.nome_guid);
  while (controllo(conducente.nome_guid))
  {
    printf("Nome del guidatore non valido, riprova: ");
    scanf("%s", conducente.nome_guid);
  }
  conducente.nome_guid[strlen(conducente.nome_guid)] = '\0';
  printf("Inserisci i posti disponibili: ");
  scanf("%d", &conducente.corsa.posti_disp);
  if (conducente.corsa.posti_disp < 0 || conducente.corsa.posti_disp >=5)
  {
    printf("Posti disponibili non validi, riprova: ");
    scanf("%d", &conducente.corsa.posti_disp);
  }
  printf("Inserisci la partenza: ");
  scanf("%s", conducente.corsa.partenzag);
  while (controllo(conducente.corsa.partenzag))
  {
    printf("Partenza non valida, riprova: ");
    scanf("%s", conducente.corsa.partenzag);
  }
  conducente.corsa.partenzag[strlen(conducente.corsa.partenzag)] = '\0';
  printf("Inserisci la destinazione: ");
  scanf("%s", conducente.corsa.destinazione);
  while (controllo(conducente.corsa.destinazione))
  {
    printf("Destinazione non valida, riprova: ");
    scanf("%s", conducente.corsa.destinazione);
  }
  conducente.corsa.destinazione[strlen(conducente.corsa.destinazione)] = '\0';
  printf("Inserisci il costo della corsa: ");
  scanf("%f", &conducente.corsa.costo);
  if (conducente.corsa.costo < 10 || conducente.corsa.costo >400)
  {
    printf("Costo della corsa non valido, riprova: ");
    scanf("%f", &conducente.corsa.costo);
  }
  printf("Inserisci la data (giorno mese anno): ");
  scanf("%d %d %d", &conducente.data.giorno, &conducente.data.mese, &conducente.data.anno);
  valido = controlli_data(conducente.data.mese,conducente.data.giorno);
      if (conducente.data.anno <= 2022 || conducente.data.anno > 2025)
  {
    printf("Anno inserito errato, riprova: ");
    scanf("%d",&conducente.data.anno);
  }
}
// AGGIUNTA GUIDATORE
void aggiunta_viaggio() {
  FILE *file = fopen("dati.bin", "ab+");
  int seed = time(NULL);
  srand(seed);
  char lettere[MAX_LETTERE] = "abcdefghijklmnopqrstuvwxyz";
  int numeri[MAX_NUMERI] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  if (file == NULL) {
	printf("Errore durante l'apertura del file.\n");
  }else{
    // Generazione di due lettere casuali
    conducente.cod_viaggio[0] = lettere[rand() % 26];
    conducente.cod_viaggio[4] = lettere[rand() % 26];

    // Generazione dei tre numeri casuali
    for (int i = 1; i <= 3; i++) {
      conducente.cod_viaggio[i] =
          numeri[rand() % 10] + '0'; // Conversione del numero in carattere ASCII
    }
    conducente.cod_viaggio[5] = '\0'; // Terminatore della stringa
    inizializzaGuid();
    acquisizione_dati_guid();
    if (strcmp(conducente.nome_guid, "Giovanni") == 0) {
      conducente.corsa.valutazione = 4.2f;
    } else if (strcmp(conducente.nome_guid, "Ruggiero") == 0) {
      conducente.corsa.valutazione = 3.7f;
    } else if (strcmp(conducente.nome_guid, "Francesco") == 0) {
      conducente.corsa.valutazione = 3.0f;
    } else if (strcmp(conducente.nome_guid, "Alberto") == 0) {
      conducente.corsa.valutazione = 5.0f;
    } else if (strcmp(conducente.nome_guid, "Michele") == 0) {
      conducente.corsa.valutazione = 2.7f;
    } else {
      // Assegnare una valutazione predefinita per nomi non corrispondenti
      conducente.corsa.valutazione = 3.0f;
    }
    // Scrittura del nuovo record nel file
    fwrite(&conducente, sizeof(struct Guidatore), 1, file);
    fclose(file);
  }
}


// MODIFICA CORSA
void modifica_viaggio() {
  int trovato = 0;
  char corsa_ric[MAX_COD_VIAGGIO];
  // Apriamo il file in modalità "lettura/scrittura" binaria
  FILE* file = fopen("dati.bin", "rb+");
  if (file == NULL) {
    printf("Errore durante l'apertura del file.\n");
  } else {
    stampa_viaggio();
    printf("Inserisci il codice della corsa da modificare: ");
    scanf("%s", corsa_ric);
    corsa_ric[5] = '\0';
    // LETTURA DEI DATI DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, file);
    while (!feof(file)) {
      if (strcmp(conducente.cod_viaggio, corsa_ric) == 0) {
        trovato = 1;
        printf("Inserisci la nuova partenza: ");
        scanf("%s", conducente.corsa.partenzag);
        printf("Inserisci la nuova destinazione: ");
        scanf("%s", conducente.corsa.destinazione);
        printf("Inserisci i nuovi posti disponibili: ");
        scanf("%d", &conducente.corsa.posti_disp);
        printf("Inserisci il nuovo costo: ");
        scanf("%f", &conducente.corsa.costo);
        // Riposizioniamo il puntatore del file alla posizione corretta
        fseek(file, -(long)sizeof(struct Guidatore), SEEK_CUR);
        // Scriviamo la corsa modificata nel file
        fwrite(&conducente, sizeof(struct Guidatore), 1, file);
        printf("La corsa con codice %s è stata modificata con successo.\n", corsa_ric);
        break;
      }
      fread(&conducente, sizeof(struct Guidatore), 1, file);
    }
    if (!trovato) {
      printf("Errore: corsa con codice %s non trovata.\n", corsa_ric);
    }
    // Chiudiamo il file
    fclose(file);
  }
}


// RIMOZIONE DI UNA CORSA SPECIFICA
void rimuovi_viaggio() {
  char codice[MAX_COD_VIAGGIO];
  int trovato = 0;
  stampa_viaggio();
  printf("Inserisci il codice della corsa da eliminare: ");
  scanf("%s", codice);
  FILE* file = fopen("dati.bin", "rb+");
  if (file == NULL) {
    printf("Errore durante l'apertura del file.\n");
  } else {
    // LETTURA DEI DATI DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, file);
    while (!feof(file)) {
      if (strcmp(conducente.cod_viaggio, codice) == 0) {
        trovato = 1;
        // Cancella la riga corrente nel file
        fseek(file, -(long)sizeof(struct Guidatore), SEEK_CUR);
        memset(&conducente, 0, sizeof(struct Guidatore));
        fwrite(&conducente, sizeof(struct Guidatore), 1, file);
        break;
      }
      fread(&conducente, sizeof(struct Guidatore), 1, file);
    }
    fclose(file);
    if (trovato) {
      printf("Corsa eliminata con successo\n");
    } else {
      printf("Nessuna corsa trovata con il codice specificato\n");
    }
  }
}

