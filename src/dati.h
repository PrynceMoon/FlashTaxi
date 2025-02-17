#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATI_H_
#define DATI_H_



// DEFINISCO LA LUNGHEZZA PER LE VARIABILI CHAR INERENTE AI GUIDATORI
#define MAX_NOME 50
#define MAX_COGNOME 50
#define MAX_DESTINAZIONE 50
#define MAX_NOTE 20
#define MAX_COD_VIAGGIO 6
#define MAX_PARTENZA 50
#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_LETTERE 26
#define MAX_NUMERI 10

struct Viaggio{
  int posti_disp;
  float costo;
  char partenzag[MAX_PARTENZA];
  char destinazione[MAX_DESTINAZIONE];
  float valutazione;
  char note[MAX_NOTE];
};

struct Data {
    int giorno;
    int anno;
    int mese;
};

// STRUTTURA DATI INERENTE AL GUIDATORE
struct Guidatore {
  char cod_viaggio[MAX_COD_VIAGGIO];
  char nome_guid[MAX_NOME];
  struct Viaggio corsa;
  struct Data data;
};

// STRUTTURA DATI INERENTE ALLA REGISTRAZIONE, UNA VOLTA REGISTRATI I DATI VERRANNO CARICATI NELL'APPOSITO FILE
struct Registrazione {
  char reg_nome[MAX_NOME];
  char reg_cognome[MAX_COGNOME];
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];
};

/* 
 * Se la macro DATI_IMPLEMENTATION è definita, viene fatta la definizione,
 * altrimenti la variabile viene dichiarata come esterna.
 */
#ifdef DATI_IMPLEMENTATION
    struct Guidatore conducente;
    struct Registrazione r;
#else
    extern struct Guidatore conducente;
    extern struct Registrazione r;
#endif

#endif /* DATI_H_ */