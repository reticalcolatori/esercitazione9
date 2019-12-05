#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fattore.h"

#define N 10	//dimensione tabella Output

/*STRUTTURA DATI CHE CONTIENE TUTTE LE INFORMAZIONI RELATIVE AD UN CANDIDATO*/
typedef struct{
	char* candidato;
	char* giudice;
	char categoria ;
	char* nomeFile;
	char fase;
	int voto;
} Riga;

//variabili globali statiche
static Riga tabella[N];
static int inizializzato = 0;


/*Stato interno parzialmente implementato*/
void inizializza(){
	int i;
	if (inizializzato == 1) return;

	for (i = 0; i < N; i++){

		tabella[i].candidato = malloc(2);
		strcpy(tabella[i].candidato, "L");

		tabella[i].giudice = malloc(2);
		strcpy(tabella[i].giudice, "L");

		tabella[i].categoria = 'L';

		tabella[i].nomeFile = malloc(2);
		strcpy(tabella[i].nomeFile, "L");

		tabella[i].fase = 'L';

		tabella[i].voto = -1;
	}

	free(tabella[1].candidato);
	tabella[1].candidato = malloc(strlen("Aldo") + 1);
	strcpy(tabella[1].candidato, "Aldo");
	free(tabella[1].giudice);
	tabella[1].giudice = malloc(strlen("Mika") + 1);
	strcpy(tabella[1].giudice, "Mika");
	tabella[1].categoria = 'U';
	free(tabella[1].nomeFile);
	tabella[1].nomeFile = malloc(strlen("AldoProfile.txt") + 1);
	strcpy(tabella[1].nomeFile, "AldoProfile.txt");
	tabella[1].fase = 'A';
	tabella[1].voto = 100;

	free(tabella[2].candidato);
	tabella[2].candidato = malloc(strlen("Giovanni") + 1);
	strcpy(tabella[2].candidato, "Giovanni");
	free(tabella[2].giudice);
	tabella[2].giudice = malloc(strlen("Mara") + 1);
	strcpy(tabella[2].giudice, "Mara");
	tabella[2].categoria = 'D';
	free(tabella[2].nomeFile);
	tabella[2].nomeFile = malloc(strlen("GiovanniProfile.txt") + 1);
	strcpy(tabella[2].nomeFile, "GiovanniProfile.txt");
	tabella[2].fase = 'S';
	tabella[2].voto = 50;

	free(tabella[3].candidato);
	tabella[3].candidato = malloc(strlen("Giacomo") + 1);
	strcpy(tabella[3].candidato, "Giacomo");
	free(tabella[3].giudice);
	tabella[3].giudice = malloc(strlen("Manuel") + 1);
	strcpy(tabella[3].giudice, "Manuel");
	tabella[3].categoria = 'D';
	free(tabella[3].nomeFile);
	tabella[3].nomeFile = malloc(strlen("GiacomoProfile.txt") + 1);
	strcpy(tabella[3].nomeFile, "GiacomoProfile.txt");
	tabella[2].fase = 'S';
	tabella[3].voto = 200;

	inizializzato = 1;
	printf("Terminata inizializzazione struttura dati!\n");
}

//implementazione delle procedure definite nel file XDR
ClassificaGiudici * classifica_giudici_1_svc(void * voidValue, struct svc_req *reqstp){
	static ClassificaGiudici result;  //array di strutture output definite nel file XDR
	GiudicePunteggio res;  //puntatore da restituire come risultato
	int i, k, presente, ind=0, max;
	inizializza();
	
	// inizializzo result a tutti valori "L"
	for(i=0; i<N; i++){
		result.currGiudice[i].nomeGiudice = malloc(2);
		strcpy(result.currGiudice[i].nomeGiudice, "L");
		result.currGiudice[i].punteggioTot = -1;
	}

	//ciclo sulla tabella
	for (i=0; i < N; i++){
		presente = 0;

		//se il giudice è già stato inserito nella tabella result aggiorno il numero dei voti e setto presente
		for(k=0; k<N; k++){
			if(strcmp(result.currGiudice[k].nomeGiudice, tabella[i].giudice)==0){
				result.currGiudice[k].punteggioTot += tabella[i].voto;
				presente = 1;
			} 
		}

		//se il giudice non era presente lo aggiungo e aggiorno il numero dei voti
		if(presente == 0){
			free(result.currGiudice[i].nomeGiudice);
			result.currGiudice[ind].nomeGiudice = malloc(strlen(tabella[i].giudice) + 1);
			strcpy(result.currGiudice[ind].nomeGiudice, tabella[i].giudice);
			result.currGiudice[ind].punteggioTot = tabella[i].voto;
			ind++;
		}
	}
	
	for (int i = 0; i < ind; i++)
	{
		printf("%s\t%d\n", result.currGiudice[i].nomeGiudice, result.currGiudice[i].punteggioTot);
	}
	

	for (int i = 0; i < ind; i++) {
		for (int j = 0; j < ind-i-1; j++) {
			if (result.currGiudice[j].punteggioTot > result.currGiudice[j+1].punteggioTot) {
				res = result.currGiudice[j];
				//printf("%s\t%d\n", res.nomeGiudice, res.punteggioTot);
				result.currGiudice[j] = result.currGiudice[j+1];
				result.currGiudice[j+1] = res;
			}
		}	
	}

	for (int i = 0; i < ind; i++)
	{
		printf("%s\t%d\n", result.currGiudice[i].nomeGiudice, result.currGiudice[i].punteggioTot);
	}

	return (&result);
	

	/*
	res = malloc(sizeof(Output));
	res->punteggioTot = -1;
	printf("ind: %d\n", ind);

	for(i=0; i<ind; i++){
		if(res->punteggioTot < result[i].punteggioTot){
			res->nomeGiudice = malloc(strlen(result[i].nomeGiudice) + 1); \babboh
			strcpy(res->nomeGiudice, result[i].nomeGiudice);
			res->punteggioTot = result[i].punteggioTot;
		}
	}

	printf("Risultato giudice_in_testa: \n\tabella Nome = %s \n\tabella Voto = %d\n", res->nomeGiudice, res->punteggioTot);
	return res;
	*/
}

int * esprimi_voto_1_svc(CandOp *candOp, struct svc_req *reqstp){
	static int found;
	found = -1;
	int i, votoTot;

	inizializza();

	for (i = 0; i < N; i++){
		if (strcmp(tabella[i].candidato, candOp->candidato) == 0){
			if(strcmp(candOp->operazione, "aggiunta") == 0) 
				tabella[i].voto++;
			else if (strcmp(candOp->operazione, "sottrazione") == 0)
				if(tabella[i].voto != 0)
					tabella[i].voto--;
				else 
					return (&found);
			else
				break;
			
			votoTot=tabella[i].voto;
			found = 0;
			break;
		}
	}

	printf ("Risultato esprimi_voto: \n\tabella Cantante = %s \n\tabella Voti = %d\n", candOp->candidato, votoTot);
	return (&found);
}
