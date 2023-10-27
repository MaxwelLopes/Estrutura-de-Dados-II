#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tentativa_Quadratica.c"

int main(){
    Hash tab_hash[M];
    inicializa(tab_hash);

    inserir(tab_hash,2, "max");

    imprimir(tab_hash);

    inserir(tab_hash,12, "josue");

    inserir(tab_hash,22, "luiz");

    inserir(tab_hash,32, "guilherme");

    imprimir(tab_hash);
}