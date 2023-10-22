#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encadeIn.c"

int main(){
    abreArquivo();

    reg guilherme = criarRegistro(6,"Guilherme");
    reg luiz = criarRegistro(7,"Luiz");

    reg josue = criarRegistro(9,"Josue");
    reg hugo = criarRegistro(70,"Hugo");
    reg ubiratam = criarRegistro(17,"Ubiratam");
    reg braida = criarRegistro(20,"Braida");
    reg max = criarRegistro(13,"Max");
    reg juliana = criarRegistro(27,"Juliana");
    reg adria = criarRegistro(35,"Adria");

    ler();

    inserir(guilherme);
    ler();

    inserir(luiz);
    ler();

    inserir(josue);
    ler();

    inserir(hugo);
    ler();

    inserir(ubiratam);
    ler();

    inserir(braida);
    ler();

    inserir(max);
    ler();


    remover(20);
    ler();

    inserir(juliana);
    ler();

    fechaArquivo();
    return 0;
}