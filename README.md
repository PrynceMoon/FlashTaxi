# FlashTaxi

FlashTaxi è un'applicazione innovativa che simula il funzionamento di un servizio taxi, offrendo un'esperienza realistica e interattiva sia per gli appassionati di simulazioni sia per chi desidera sperimentare la gestione operativa di una flotta di taxi. Il progetto è stato sviluppato con l'obiettivo di integrare logiche di business e una gestione dinamica delle richieste, rendendolo uno strumento ideale sia a scopo didattico che dimostrativo.

## Caratteristiche principali

- **Simulazione Realistica**: 
  - Riproduzione fedele del ciclo di vita di una corsa, dalla richiesta di un passeggero al completamento del servizio.

- **Sistema di Dispatch Dinamico**: 
  - Ottimizzazione delle rotte e gestione degli itinerari tramite un'interfaccia intuitiva.

- **Modularità e Scalabilità**: 
  - Struttura del codice organizzata in moduli separati per facilitare manutenzione e futuri sviluppi.
  - Possibilità di estendere le funzionalità o integrare nuove componenti senza compromettere la stabilità dell'applicazione.

## Struttura del Progetto

Il repository è organizzato in maniera modulare per separare le diverse responsabilità del sistema:

- **Interfaccia da terminale**:  
  L'esecuzione del progetto è tutto in linea di comando/terminale del IDE con cui viene eseguito o tramite l'eseguibile presente all'interno, se optata questa scelta la completa esecuzione del progetto avverrà da terminale di windows.

- **Database**:  
  In questo progetto non è stato usato un vero e porpio DB ma un file binario che svolge il ruolo di DB, esso svolge un ruolo centrale nella gestione dei dati e delle meccaniche del gestionale. La scelta dell'utilizzo di esso è stata motivata dalla sua leggerezza e facilità d'uso. All'interno del progetto sono stati utilizzati ben 3 file binari:

  - Dati: all'interno di questo file sono presenti tutte le corse per i clienti che possono essere prenotate, al suo interno sono presenti varie tratte. 
  - Cronologia: all'interno di questo file sono presenti tutte le corse che sono state eseguite dai vari clienti che hanno usato il gestionale.
  - Utenti: all'interno di questo file sono presenti tutte le credenziali degli utenti che si sono registrati e che hanno o vorranno in futuro prenotare una corsa dal gestionale.

## Descrizione dei file principali
- **esame.c**:
  *Parte principale del progetto.*
  Da esso viene eseguito il programma principale, ad esso è collegato il file contenente tutte le funzioni d'accesso.
- **accesso.c**:
  *Acceesso alle 2 categorie degli utenti.*
  Una volta eseguito il programma verrà data la possibilità all'utente di accedere tramite "admin" in cui bisogna sapere anche le credenziali d'accesso oppure tramite utente.  
- **accesso_utente.c**:
  *Accesso tramite utente.*
  Se precedentemente è stato selezionato l'accecsso tramite utente, esso dovrà scegliere nuovamente ma questa voltà sceglierà se accedere se ti sei già registrato in precedenza oppure di registrarsi inserendo anche i dati fondamentali per la registrazione.
- **controlli.c**:
  *Vari controlli usati sia lato admin che lato utente.*
- **Admin**
  - **menu_admin.c**:
  *Scelte dell'admin.*
Se precedentemente è stato scelto di accedere come admin, visualizzeremo tutte le operazioni che l'admin può fare, esse sono:
    - Aggiungere una corsa;
    - Modificare una determinata corsa;
    - Rimuovere una determinata corsa;
    - Visualizzare la cronologia delle corse fatte dai clienti;
  - **funzioni_admin.c**:
    Come accennato in precedenza, se eseguito l'accesso come admin possiamo eseguire dei comandi:
    - Aggiungere una corsa: qui inseriremo tutti i campi necessari per l'inserimento della corsa all'interno del file dati.bin, verrà generato anche un codice con cui grazie ad esso sarà possibile eseguire i comandi successivi o lato cliente.
    - Modificare una determinata corsa: qui l'admin inserirà il codice della corsa che desidera modificare e successivamente se quest'ultima è presente all'interno del file sarà possibile modificare alcuni campi.
    - Rimuovere una determinata corsa: qui l'admin inserirà il codice della corsa che desidera eliminare e successivamente se quest'ultima è presente all'interno del file la corsa verrà eliminata.
    - Visualizzare la cronologia delle corse fatte dai clienti: qui l'admin visualizzerà tutte le corse che sono state eseguite dai vari clienti.
- **Utente**
  - **menu_utente.c**:
  *Scelte dell'utente.*
Se precedentemente è stato scelto di accedere come cliente, visualizzeremo tutte le operazioni che esso può fare, esse sono:
    - Prenotare una corsa;
    - Visualizzazione del guidatore con valutazione più elevata;
  - **funzioni_utente.c**:
        Come accennato in precedenza, se eseguito l'accesso come cliente possiamo eseguire dei comandi:
    - Prenotare una corsa: qui inseriremo tutti i campi necessari per la prenotazione della corsa, verranno visualizzate tutte le corse che soddisfano i criteri che ha inserito il cliente e quest'ultimo può prenotare una corsa di un conducente che visualizza semplicemente digitando il codice della corsa che visualizza.
    - Visualizzazione del guidatore con valutazione più elevata: se scelto questo comando, il cliente visualizza semplicemente il guidatore che la valutazione media maggiore rispetto a tutti gli altri guidatori.
- **stampa_viaggi.c**:
  *Visualizzazione dei viaggi.*
  In qeusto file sono presenti tutte le funzioni usate nei vari casi per la visualizzazione delle corse, essa è sia totale per lato admin che parziale in base alla soddisfazione dei requisiti per la corsa che inserisce l'utente   
## Requisiti e Installazione

### Possibili implementazioni
- trasformare l'interfaccia a linea di comando in una GUI interattiva e intuitiva, per offrire un'esperienza utente migliorata e più accessibile.
- Conversione dei file dal formato binario a formato testuale, oppure, migrando verso database strutturati.
- Calcolo accurato delle tariffe basato su parametri quali distanza, tempo e condizioni variabili.
- Dashboard integrata per monitorare le corse e visualizzare in tempo reale la posizione dei veicoli.
- Design responsive e user-friendly per un'esperienza coinvolgente.
