  
struct Output{
	string nomeGiudice <100>; 
	int punteggioTot;
}; 
  
program FATTOREX {
	version VERSFATTOREX {         
		Output CLASSIFICA_GIUDICI() = 1;        
        int ESPRIMI_VOTO(string) = 2;
	} = 1;
} = 0x20042069;
