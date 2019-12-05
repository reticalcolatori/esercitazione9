  
struct GiudicePunteggio{
	string nomeGiudice <100>; 
	int punteggioTot;
}; 

struct ClassificaGiudici{
	GiudicePunteggio currGiudice [20];
};

struct CandOp{
	string candidato <100>;
	string operazione <20>;
};
  
program FATTOREX {
	version VERSFATTOREX {         
		ClassificaGiudici CLASSIFICA_GIUDICI(void) = 1;        
        int ESPRIMI_VOTO(CandOp) = 2;
	} = 1;
} = 0x20000010;
