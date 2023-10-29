#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tentativa_Quadratica.c"

int main(){
    Hash tab_hash[M];
    inicializa(tab_hash);

    inserir(tab_hash,1, "max");
    imprimir(tab_hash);

    inserir(tab_hash,11, "josue");
    imprimir(tab_hash);

    inserir(tab_hash,21, "luiz");
    imprimir(tab_hash);

    inserir(tab_hash,31, "guilherme");
    imprimir(tab_hash);

    
}