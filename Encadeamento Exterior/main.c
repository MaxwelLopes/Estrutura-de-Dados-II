#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encadeEx.c"
#define M 7

int main(){
    char* tabHash = "tabHash.dat";
    char* cliente = "cliente.dat";
    
    FILE* tabelaHash = fopen(tabHash,"w+b");
    FILE* clientes = fopen(cliente,"w+b");
    inicializaHash(tabelaHash);

    reg joao;
    joao.codCliente = 49;
    strcpy(joao.nome,"Joao");
    joao.prox = -1;
    joao.status = 0;

    reg maria;
    maria.codCliente = 59;
    strcpy(maria.nome,"Maria");
    maria.prox = -1;
    maria.status = 0;

    reg ana;
    ana.codCliente = 103;
    strcpy(ana.nome,"Ana");
    ana.prox = -1;
    ana.status = 0;

    reg jose;
    jose.codCliente = 3;
    strcpy(jose.nome,"Jose");
    jose.prox = -1;
    jose.status = 0;

    reg carla;
    carla.codCliente = 51;
    strcpy(carla.nome,"Carla");
    carla.prox = -1;
    carla.status = 0;

    reg bia;
    bia.codCliente = 87;
    strcpy(bia.nome,"Bia");
    bia.prox = -1;
    bia.status = 0;

    inserir(tabelaHash, clientes, joao);
    inserir(tabelaHash, clientes, maria);
    inserir(tabelaHash, clientes, ana);
    inserir(tabelaHash, clientes, jose);
    inserir(tabelaHash, clientes, carla);
    inserir(tabelaHash, clientes, bia);

    ler(tabelaHash, clientes);

    fclose(tabelaHash);
    fclose(clientes);  

    return 0;
}