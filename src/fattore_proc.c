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

	//Inizializzazione della tabella
	//Dato che le variabili static vengono impostate a zero non devo usare la memset.

	static char liberoString[2];
	char *liberoStringPointer = liberoString;
	liberoString[i] = 'L';
	liberoString[i+1] = '\0';
	
	for(int i = 0; i < N; i++){
		tabella[i].candidato = liberoStringPointer;
		tabella[i].giudice = liberoStringPointer;
		tabella[i].categoria = 'L';
		tabella[i].nomeFile = liberoStringPointer;
		tabella[i].fase = 'L';
		tabella[i].voto = -1;
	}

	//Inizializzazione vera e propria
	const char *nomeCandidato0 = "Pippo";
	tabella[0].candidato = malloc(sizeof(char) * (strlen(nomeCandidato0)+1));
	strcpy(tabella[0].candidato, nomeCandidato0);
	//e cosi via da finire....
	

}

int * esprimi_voto_1_svc(char **, struct svc_req *){



}

Output * classifica_giudici_1_svc(void *, struct svc_req *){

}

