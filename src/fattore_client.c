#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "fattore.h"

#define DIM 256
#define N 10

int main (int argc, char *argv[])
{
	/* 
     * PASSI PER IL DEPLOY DEL CLIENT
     * 1) Controllo argomenti
     * 2) Genero il gestore di trasporto lato cliente
     * 3) Chiedo ciclicamente all'utente l'operazione e i parametri necessari per eseguirla
     * 4) Riparto
    */ 

    CLIENT *client;
    char *server;
    void *in;
    ClassificaGiudici *res;

    if(argc != 2) {
        perror("Usage: client nameServer");
        exit(EXIT_FAILURE);
    }

    //strcpy(server, argv[1]);
    server = argv[1];

    client = clnt_create(server, FATTOREX, VERSFATTOREX, "udp");
    if(client == NULL) {
        clnt_pcreateerror(server);
        exit(EXIT_FAILURE);
    }

    char currOp[DIM];
    printf("Inserisci il tipo di operazione:\n");

    while (gets(currOp)) {
        if (currOp[0] == 'C'|| currOp[0] == 'c') {
            
            res = classifica_giudici_1(in, client);
            if(res == NULL) {
                clnt_perror(client, "Errore durante ricezione classifica\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < N; i++) {
                printf("%s\t%d\n", res->currGiudice[i].nomeGiudice, res->currGiudice[i].punteggioTot);
            }
        }

        else if (currOp[0] == 'V' || currOp[0] == 'v') {

            printf("Chi vuoi votare?\n");
            
            char nomeCandidato[100];
            gets(nomeCandidato);

            printf("aggiunta/sottrazione?\n");

            char op[20];
            gets(op);

            CandOp candOp;
            strcpy(candOp.candidato, nomeCandidato);
            strcpy(candOp.operazione, op);
            
            int *res = esprimi_voto_1(&candOp, client);
            if(res == NULL) {
                clnt_perror(client, "Errore durante ricezione esito aggiunta voto\n");
                exit(EXIT_FAILURE);
            }

            if(*res < 0) 
                printf("Impossibile completare operazione richiesta\n");
            else
                printf("Operazione completata con successo\n");
        }

        else
            printf("Operazione non disponibile.\n");

        printf("Inserisci il tipo di operazione:\n");
        
    }

    clnt_destroy(client);
    exit(EXIT_SUCCESS);

}//main