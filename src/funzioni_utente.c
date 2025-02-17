#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "controlli.h"
#include "menu_utente.h"
#include "dati.h"
#include "stampa_viaggi.h"

// INIZIALIZZAZIONE DEI CAMPI DELLA STRUCT
void inizializzaUte(int* giorno, int* mese, int* anno, int* num_passeggeri){
  mese=0;
  giorno=0;
  anno=0;
  num_passeggeri=0;
}

// ACQUISIZIONE DATI UTENTE
void acquisizione_dati_ute(char* partenza, char* destinazione, int* giorno, int* mese, int* anno, int* num_passeggeri) {
  int valido;

  printf("Inserisci la partenza: ");
  scanf("%s", partenza);
  while (controllo(partenza)) {
    printf("Partenza non valida, riprova: ");
    scanf("%s", partenza);
  }
  partenza[strlen(partenza)] = '\0';

  printf("Inserisci la destinazione: ");
  scanf("%s", destinazione);
  while (controllo(destinazione)) {
    printf("Destinazione non valida, riprova: ");
    scanf("%s", destinazione);
  }
  destinazione[strlen(destinazione)] = '\0';

  printf("Inserisci la data (giorno mese anno): ");
  scanf("%d %d %d", giorno, mese, anno);
  valido = controlli_data(*mese, *giorno);
  if (*anno <= 2022 || *anno > 2025) {
    printf("Anno inserito errato, riprova: ");
    scanf("%d", anno);
  }

  printf("Inserisci il numero di passeggeri: ");
  scanf("%d", num_passeggeri);
}


// PRENOTAZIONE DELLA CORSA SELEZIONATA DALL'UTENTE IN BASE ALLE INFORMAZIONI INSERITE
void prenotazione() {
    char nometemp[MAX_NOME];
    int trovato;
    char partenza[MAX_PARTENZA];
    char cod_viaggio_selezionato[MAX_COD_VIAGGIO];
    float val;
    char destinazione[MAX_DESTINAZIONE];
    int giorno, mese, anno, num_passeggeri;
    int codice_errato = 0; // Flag per indicare se è stato inserito un codice errato
    int valutazione_aggiornata = 0; // Flag per indicare se la valutazione del conducente è stata aggiornata

    acquisizione_dati_ute(partenza, destinazione, &giorno, &mese, &anno, &num_passeggeri);

    FILE* fpp = fopen("dati.bin", "rb+");
    if (fpp == NULL) {
        printf("Errore nell'apertura del file dei dati delle corse\n");
        // Continua l'esecuzione anche se il file non si apre
    }
    else {
        stamparicerca(&trovato, partenza, destinazione, giorno, mese, anno, num_passeggeri);
        if (trovato == 1) {
            printf("Inserisci il codice del viaggio desiderato: ");
            scanf("%s", cod_viaggio_selezionato);
            rewind(fpp);
            fread(&conducente, sizeof(struct Guidatore), 1, fpp);
            while (!feof(fpp)) {
                if (strcmp(conducente.cod_viaggio, cod_viaggio_selezionato) == 0) {
                    strcpy(nometemp, conducente.nome_guid);
                    printf("---------------------------------------------------------------\n");
                    printf("Hai selezionato il seguente viaggio:\n");
                    printf("Codice corsa: %s\n", conducente.cod_viaggio);
                    printf("Nome guidatore: %s\n", conducente.nome_guid);
                    printf("Partenza: %s\n", conducente.corsa.partenzag);
                    printf("Destinazione: %s\n", conducente.corsa.destinazione);
                    printf("Costo: %.2f\n", conducente.corsa.costo);
                    printf("Data: %02d/%02d/%04d\n", conducente.data.giorno, conducente.data.mese, conducente.data.anno);
                    printf("---------------------------------------------------------------\n");
                    sleep(7);

                    // Salva le informazioni del viaggio nella cronologia
                    FILE* fcc = fopen("cronologia.bin", "ab+");
                    if (fcc == NULL) {
                        printf("Errore nell'apertura del file cronologia\n");
                        // Continua l'esecuzione anche se il file cronologia non si apre
                    }
                    else {
                        fseek(fcc, 0, SEEK_END); // Posizionati alla fine del file "cronologia.bin"
                        barra_di_caricamento_accettazioneviaggio();
                        barra_di_caricamento_simulazioneviaggio();

                        do {
                            printf("Lasciare una valutazione alla corsa effettuata: ");
                            if (scanf("%f", &val) != 1) {
                                printf("Hai inserito un valore non valido. Riprova.\n");
                                while (getchar() != '\n') {} // Pulizia del buffer di input
                                continue;
                            }
                            if (val <= 0 || val > 5) {
                                printf("Lasciare una valutazione corretta alla corsa effettuata (compresa tra 1 e 5): ");
                            }
                        } while (val <= 0 || val > 5);

                        val = (val + conducente.corsa.valutazione) / 2;
                        conducente.corsa.valutazione = val;
                        fwrite(&conducente, sizeof(struct Guidatore), 1, fcc);
                        fclose(fcc);

                        // Elimina la corsa selezionata dal file
                        fseek(fpp, -((long long)sizeof(struct Guidatore)), SEEK_CUR);
                        memset(&conducente, 0, sizeof(struct Guidatore));
                        fwrite(&conducente, sizeof(struct Guidatore), 1, fpp);

                        // Aggiorna la valutazione delle corse rimanenti del conducente
                        rewind(fpp);
                        fread(&conducente, sizeof(struct Guidatore), 1, fpp);
                        while (!feof(fpp)) {
                            if (strcmp(conducente.nome_guid, nometemp) == 0) {
                                conducente.corsa.valutazione = val; // Assegna la nuova valutazione al record corrente
                                fseek(fpp, -((long long)sizeof(struct Guidatore)), SEEK_CUR);
                                fwrite(&conducente, sizeof(struct Guidatore), 1, fpp);
                                if (!valutazione_aggiornata) {
                                    printf("Valutazione del conducente è stata aggiornata\n");
                                    valutazione_aggiornata = 1; // Imposta il flag a 1 per indicare che la valutazione è stata aggiornata
                                }
                            }
                            fread(&conducente, sizeof(struct Guidatore), 1, fpp);
                        }
                        printf("Corsa eliminata con successo\n");
                        codice_errato = 0; // Il codice è stato trovato correttamente, reimposta il flag a 0
                    }
                }
                else {
                    codice_errato = 1;
                }
                fread(&conducente, sizeof(struct Guidatore), 1, fpp);
            }

            if (codice_errato) {
                printf("Codice corsa errato\n");
            }
        }
        fclose(fpp);
    }
}
