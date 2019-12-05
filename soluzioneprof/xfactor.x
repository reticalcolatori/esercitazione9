  
struct Output{
	string nomeGiudice <256>; 
	int punteggioTot;
}; 
  
program OPERATION {
	version OPERATIONVERS {         
		Output GIUDICE_IN_TESTA() = 1;        
        int ESPRIMI_VOTO(string) = 2;
	} = 1;
} = 0x20000013;

