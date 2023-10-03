#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encadeEx.c"
#define M 7

int main(){

    abreArquivo();

    reg joao = criarRegistro(49,"João");
    reg maria = criarRegistro(59,"Maria");;
    reg ana = criarRegistro(103,"Ana");
    reg jose = criarRegistro(3,"Jose");
    reg carla = criarRegistro(51,"Carla");
    reg bia = criarRegistro(87,"Bia");
    reg ubiratam = criarRegistro(17, "Ubiratam");
    reg guilherme = criarRegistro(66, "Guilherme");
    reg luiz = criarRegistro(20, "Luiz");

    inserir(joao);
    inserir(maria);
    inserir(ana);
    inserir(jose);
    inserir(carla);
    inserir(bia);

    ler(); 

    //remover(3);
    ler();

    inserir(ubiratam);
    ler();

    inserir(guilherme);
    ler();

    inserir(luiz);
    ler();

    

    int teste = busca(20,1);

    fseek(clientes, teste * sizeof(reg), SEEK_SET);
    strcpy(luiz.nome, "luiz Filipe");
    fwrite(&luiz, sizeof(reg), 1, clientes);
    fflush(clientes);
    ler();
    

    fechaArquivo();

    return 0;
}