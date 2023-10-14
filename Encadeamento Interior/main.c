#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encadeIn.c"

int main(){
    abreArquivo();
    
    reg guilherme = criarRegistro(28,"Guilherme");
    reg luiz = criarRegistro(35,"Luiz");
    reg max = criarRegistro(14,"Max");
    reg josue = criarRegistro(9,"Josue");
    reg hugo = criarRegistro(70,"Hugo");
    reg ubiratam = criarRegistro(13,"Ubiratam");
    reg braida = criarRegistro(12,"Braida");
    reg juliana = criarRegistro(12,"Juliana");
    
    ler();

    inserir(guilherme);
    inserir(luiz);
    inserir(max);
    inserir(josue);
    inserir(hugo);
    inserir(ubiratam);
    inserir(braida);

    ler();

    remover(12);

    ler();

    inserir(juliana);

    ler();

    fechaArquivo();
    return 0;
}