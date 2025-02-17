#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "dati.h"
#include "menu_utente.h"

void stamparicerca(int* trovato, const char* partenza, const char* destinazione, int giorno, int mese, int anno, int num_passeggeri) {
  int num_corse = 0; // Contatore per il numero di corse trovate
  int i = 0; // Indice per l'array di corse trovate
  struct Guidatore* corse_trovate = NULL;
  FILE* fpp = fopen("dati.bin", "rb+");
  if (fpp == NULL) {
    printf("Errore nell'apertura del file dei dati delle corse\n");
    printf("Impossibile stampare i risultati della ricerca\n");
  } else {
    // LETTURA DEI DATI DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, fpp);
    while (!feof(fpp)) {
      if (strcmp(conducente.corsa.partenzag, partenza) == 0 &&
          strcmp(conducente.corsa.destinazione, destinazione) == 0 &&
          conducente.data.giorno == giorno &&
          conducente.data.mese == mese &&
          conducente.data.anno == anno &&
          conducente.corsa.posti_disp >= num_passeggeri) {
        num_corse++;
        *trovato = 1;
      }
      fread(&conducente, sizeof(struct Guidatore), 1, fpp);
    }

    if (num_corse == 0) {
      printf("Nessuna corsa trovata\n");
      *trovato = 0;
    } else {
      // Riportare il puntatore del file all'inizio
      fseek(fpp, 0, SEEK_SET);

      // Allocazione dinamica dell'array di corse trovate
      corse_trovate = malloc(num_corse * sizeof(struct Guidatore));
      if (corse_trovate == NULL) {
        printf("Errore nell'allocazione della memoria\n");
      } else {
        // Popolare l'array con le corse trovate
        fread(&conducente, sizeof(struct Guidatore), 1, fpp);
        while (!feof(fpp)) {
          if (strcmp(conducente.corsa.partenzag, partenza) == 0 &&
              strcmp(conducente.corsa.destinazione, destinazione) == 0 &&
              conducente.data.giorno == giorno &&
              conducente.data.mese == mese &&
              conducente.data.anno == anno &&
              conducente.corsa.posti_disp >= num_passeggeri) {

            // Creare una copia temporanea della struttura Guidatore
            struct Guidatore corsa_trovata;
            strcpy(corsa_trovata.cod_viaggio, conducente.cod_viaggio);
            strcpy(corsa_trovata.nome_guid, conducente.nome_guid);
            corsa_trovata.corsa = conducente.corsa;
            corsa_trovata.data = conducente.data; // Aggiungere questa riga per copiare la data correttamente

            // Aggiungere la corsa trovata all'array
            corse_trovate[i] = corsa_trovata;
            i++;
          }
          fread(&conducente, sizeof(struct Guidatore), 1, fpp);
        }

        // Ordinare l'array di corse trovate in base al costo (prezzo)
        for (int j = 0; j < num_corse - 1; j++) {
          for (int k = 0; k < num_corse - j - 1; k++) {
            if (corse_trovate[k].corsa.costo > corse_trovate[k + 1].corsa.costo) {
              struct Guidatore temp = corse_trovate[k];
              corse_trovate[k] = corse_trovate[k + 1];
              corse_trovate[k + 1] = temp;
            }
          }
        }

        // Stampa delle corse in ordine di prezzo (dal più economico al più caro)
        printf("%-15s | %-18s | %-12s | %-13s | %-8s | %-10s | %-10s\n",
               "Codice corsa", "Nome guidatore", "Partenza", "Destinazione", "Costo", "Data", "Valutazione");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (int j = 0; j < num_corse; j++) {
          printf("%-15s | %-18s | %-12s | %-13s | %-8.2f | %02d/%02d/%04d | %.2f\n",
                 corse_trovate[j].cod_viaggio, corse_trovate[j].nome_guid, corse_trovate[j].corsa.partenzag,
                 corse_trovate[j].corsa.destinazione, corse_trovate[j].corsa.costo, corse_trovate[j].data.giorno,
                 corse_trovate[j].data.mese, corse_trovate[j].data.anno, corse_trovate[j].corsa.valutazione);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
        // Liberare la memoria allocata per l'array di corse trovate
        free(corse_trovate);
      }
    }
    // Chiudere il file
    fclose(fpp);
  }
}





// STAMPO A VIDEO TUTTI I VIAGGI DEI GUIDATORI PRESENTI, SERVE PER IL LATO ADMIN NELLA MODIFICA O RIMOZIONE DEI VIAGGI
void stampa_viaggio() {
  FILE *fp;
  int record_valido = 1;
  fp = fopen("dati.bin", "rb");
  if (fp == NULL) {
    printf("Errore durante l'apertura del file.\n");
  } else {
    // LETTURA DEI DATI DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, fp);
    printf("%-14s | %-16s | %-12s | %-8s | %-12s | %-16s | %-4s | %-11s\n",
           "Codice viaggio", "Nome guidatore", "Posti disp.", "Costo", "Partenza",
           "Destinazione", "Valutazione", "Data");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while (!feof(fp)) {
      // Controllo se ogni campo del record è valido
      if (strlen(conducente.cod_viaggio) == 0 ||
          strlen(conducente.nome_guid) == 0 || conducente.corsa.posti_disp == 0 ||
          conducente.corsa.costo == 0 || strlen(conducente.corsa.partenzag) == 0 ||
          strlen(conducente.corsa.destinazione) == 0 || conducente.corsa.valutazione == 0 ||
          conducente.data.giorno == 0 || conducente.data.mese == 0 || conducente.data.anno == 0) {
        record_valido = 0;
      }
      if (record_valido) {
        printf("%-14s | %-16s | %-12d | %-8.2f | %-12s | %-16s | %-11.2f | "
               "%02d/%02d/%04d\n",
               conducente.cod_viaggio, conducente.nome_guid, conducente.corsa.posti_disp,
               conducente.corsa.costo, conducente.corsa.partenzag, conducente.corsa.destinazione,
               conducente.corsa.valutazione, conducente.data.giorno, conducente.data.mese,
               conducente.data.anno);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
      }
      record_valido = 1;  // Reimposta il flag record_valido a 1 per il prossimo record
      fread(&conducente, sizeof(struct Guidatore), 1, fp);
    }
    fclose(fp);
  }
}


// STAMPO A VIDEO TUTTE LE CORSE CHE GLI UTENTI HANNO SELEZIONATO
void cronologia() {
  FILE *fp;
  int record_valido = 1;
  fp = fopen("cronologia.bin", "rb");
  if (fp == NULL) {
    printf("Errore durante l'apertura del file.\n");
  } else {
    // LETTURA DEI DATI DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, fp);
    printf("%-14s | %-16s | %-12s | %-8s | %-12s | %-16s | %-4s | %-11s\n",
           "Codice viaggio", "Nome guidatore", "Posti disp.", "Costo", "Partenza",
           "Destinazione", "Valutazione", "Data");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    while (!feof(fp)) {
      // Controllo se ogni campo del record è valido
      if (strlen(conducente.cod_viaggio) == 0 ||
          strlen(conducente.nome_guid) == 0 || conducente.corsa.posti_disp == 0 ||
          conducente.corsa.costo == 0 || strlen(conducente.corsa.partenzag) == 0 ||
          strlen(conducente.corsa.destinazione) == 0 || conducente.corsa.valutazione == 0 ||
          conducente.data.giorno == 0 || conducente.data.mese == 0 || conducente.data.anno == 0) {
        record_valido = 0;
      }
      if (record_valido) {
        printf("%-14s | %-16s | %-12d | %-8.2f | %-12s | %-16s | %-11.2f | "
               "%02d/%02d/%04d\n",
               conducente.cod_viaggio, conducente.nome_guid, conducente.corsa.posti_disp,
               conducente.corsa.costo, conducente.corsa.partenzag, conducente.corsa.destinazione,
               conducente.corsa.valutazione, conducente.data.giorno, conducente.data.mese,
               conducente.data.anno);
      }
      record_valido = 1;  // Reimposta il flag record_valido a 1 per il prossimo record
      fread(&conducente, sizeof(struct Guidatore), 1, fp);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    sleep(10);
    fclose(fp);
  }
}




// STAMPO A VIDEO IL GUIDATORE CHE POSSIEDE LA VALUTAZIONE PIU' ALTA
void stampa_guidatore_valutazione_massima() {
  FILE *file = fopen("dati.bin", "rb");
  if (file == NULL) {
    printf("Errore nell'apertura del file\n");
  } else {
    struct Guidatore guidatore_valutazione_massima;
    float valutazione_massima = 0.0;

    // LETTURA DEL PRIMO RECORD DAL FILE
    fread(&conducente, sizeof(struct Guidatore), 1, file);

    while (!feof(file)) {
      if (conducente.corsa.valutazione > valutazione_massima) {
        valutazione_massima = conducente.corsa.valutazione;
        guidatore_valutazione_massima = conducente;
      }
      fread(&conducente, sizeof(struct Guidatore), 1, file);
    }

    fclose(file);

    if (valutazione_massima > 0.0) {
      printf("Conducente con la valutazione più alta:\n");
      printf("Nome: %s\n", guidatore_valutazione_massima.nome_guid);
      printf("Valutazione: %.2f\n", guidatore_valutazione_massima.corsa.valutazione);
    } else {
      printf("Nessun conducente trovato con valutazione\n");
    }
  }
}
