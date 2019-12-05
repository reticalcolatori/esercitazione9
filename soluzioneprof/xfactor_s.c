/*
 * xfactor_s.c
 */

#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xfactor.h"

#define N 5	//dimensione tabella Output

/*STATO INTERNO PRIVATO DEL SERVER*/
typedef struct{
	char* candidato;
	char* giudice;
	char categoria ;
	char* nomeFile;
	char fase;
	int voto;
} Riga;

//variabili globali statiche
static Riga t[N];
static int inizializzato = 0;


/*Stato interno parzialmente implementato*/
void inizializza(){
	int i;
	if (inizializzato == 1) return;

	for (i = 0; i < N; i++){

		t[i].candidato = malloc(2);
		strcpy(t[i].candidato, "L");

		t[i].giudice = malloc(2);
		strcpy(t[i].giudice, "L");

		t[i].categoria = 'L';

		t[i].nomeFile = malloc(2);
		strcpy(t[i].nomeFile, "L");

		t[i].fase = 'L';

		t[i].voto = -1;
	}

	free(t[1].candidato);
	t[1].candidato = malloc(strlen("Brasco") + 1);
	strcpy(t[1].candidato, "Brasco");
	free(t[1].giudice);
	t[1].giudice = malloc(strlen("Bowie") + 1);
	strcpy(t[1].giudice, "Bowie");
	t[1].categoria = 'U';
	free(t[1].nomeFile);
	t[1].nomeFile = malloc(strlen("BrascoProfile.txt") + 1);
	strcpy(t[1].nomeFile, "BrascoProfile.txt");
	t[1].fase = 'A';
	t[1].voto = 100;

	free(t[2].candidato);
	t[2].candidato = malloc(strlen("Viga") + 1);
	strcpy(t[2].candidato, "Viga");
	free(t[2].giudice);
	t[2].giudice = malloc(strlen("Winehouse") + 1);
	strcpy(t[2].giudice, "Winehouse");
	t[2].categoria = 'D';
	free(t[2].nomeFile);
	t[2].nomeFile = malloc(strlen("alfredo.txt") + 1);
	strcpy(t[2].nomeFile, "alfredo.txt");
	t[2].fase = 'S';
	t[2].voto = 50;

	free(t[3].candidato);
	t[3].candidato = malloc(strlen("Pippo") + 1);
	strcpy(t[3].candidato, "Pippo");
	free(t[3].giudice);
	t[3].giudice = malloc(strlen("Bowie") + 1);
	strcpy(t[3].giudice, "Bowie");
	t[3].categoria = 'D';
	free(t[3].nomeFile);
	t[3].nomeFile = malloc(strlen("canzone.txt") + 1);
	strcpy(t[3].nomeFile, "canzone.txt");
	t[2].fase = 'S';
	t[3].voto = 200;

	inizializzato = 1;
	printf("Terminata inizializzazione struttura dati!\n");
}

//implementazione delle procedure definite nel file XDR
Output * giudice_in_testa_1_svc(void * voidValue, struct svc_req *reqstp){
	Output summary[N];
	Output *res;
	int i, k, presente, ind=0, max;
	inizializza();

	// inizializza summary
	for(i=0; i<N; i++){
		summary[i].nomeGiudice = malloc(2);
		strcpy(summary[i].nomeGiudice, "L");
		summary[i].punteggioTot = -1;
	}



	for (i=0; i < N; i++){
		presente = 0;

		for(k=0; k<N; k++){
			if(strcmp(summary[k].nomeGiudice, t[i].giudice)==0){
				summary[k].punteggioTot = summary[k].punteggioTot + t[i].voto;
				presente = 1;
			} 
		}

		if(presente == 0){
			free(summary[ind].nomeGiudice);
			summary[ind].nomeGiudice = malloc(strlen(t[i].giudice) + 1);
			strcpy(summary[ind].nomeGiudice, t[i].giudice);
			summary[ind].punteggioTot = t[i].voto;
			ind++;
		}
	}

	res = malloc(sizeof(Output));
	res->punteggioTot = -1;
	printf("ind: %d\n", ind);

	for(i=0; i<ind; i++){
		if(res->punteggioTot < summary[i].punteggioTot){
			res->nomeGiudice = malloc(strlen(summary[i].nomeGiudice) + 1);
			strcpy(res->nomeGiudice, summary[i].nomeGiudice);
			res->punteggioTot = summary[i].punteggioTot;
		}
	}

	printf("Risultato giudice_in_testa: \n\t Nome = %s \n\t Voto = %d\n", res->nomeGiudice, res->punteggioTot);
	return res;
}

int * esprimi_voto_1_svc(char **s, struct svc_req *reqstp){
	static int found;
	found = -1;
	int i, votoTot;

	inizializza();

	for (i = 0; i < N; i++){
		if (strcmp(t[i].candidato, *s) == 0){
			t[i].voto++;
			votoTot=t[i].voto;
			found = 0;
			break;
		}
	}

	printf ("Risultato esprimi_voto: \n\t Cantante = %s \n\t Voti = %d\n", *s, votoTot);
	return (&found);
}
