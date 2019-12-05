
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

    //prova di free su stringa costante

    char *myConstString = "Ciao";


    printf("S: %s\n", myConstString);

    //free test, da manuale non si dovrebbe fare. ma noi siamo birichini
    free(myConstString);


    printf("Free completed.\nS: %s\n", myConstString);


    //OK questa cosa non si può fare.


    return 0;
}