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
    reg jose = criarRegistro(3,"Jose");;
    reg carla = criarRegistro(51,"Carla");
    reg bia = criarRegistro(87,"Bia");
    reg ubiratam = criarRegistro(7, "Ubiratam");

    inserir(joao);
    inserir(maria);
    inserir(ana);
    inserir(jose);
    inserir(carla);
    inserir(bia);

    ler(); 

    remover(49);
    ler();

    inserir(ubiratam);
    ler();

    fechaArquivo();

    return 0;
}