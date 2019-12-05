#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "fattore.h"

#define TABLE_LENGTH 6	

#define FALSE 0
#define TRUE !FALSE

/*STATO INTERNO PRIVATO DEL SERVER*/
typedef struct{
	char* candidato;
	char* giudice;
	char categoria;
	char* nomeFile;
	char fase;
	int voto;
} RigaTabella;


//Definisco la tabella come Array di righe per stare con le specifiche di XDR
static RigaTabella tabella[N];

void init(){
    //Workaround per l'inizializzazione: invece che modificare lo stub, utilizzo una variabile statica.
    static int init = FALSE;

    if(init) return;

}

int * esprimi_voto_1_svc(char **, struct svc_req *);
Output * classifica_giudici_1_svc(void *, struct svc_req *);

