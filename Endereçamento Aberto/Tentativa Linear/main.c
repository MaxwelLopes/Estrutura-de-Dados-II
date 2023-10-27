#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tentativa_Linear.c"

int main(){
    Hash tab_hash[M];
    inicializa(tab_hash);

    inserir(tab_hash,2, "max");

    imprimir(tab_hash);
    
    remover(tab_hash, 2);

    inserir(tab_hash,2, "max");

    imprimir(tab_hash);
}