#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tentativa_Linear.c"
#include "benchmark.c"

int main(){
    int tamanhoTabela = 100;
    Hash tab_hash[tamanhoTabela];
    float fator_carga = 0.7;
    int numero_registro;
    int numero_teste = 100;
    
    inicializa(tab_hash, tamanhoTabela);
    benchmarkInsercao(tab_hash, fator_carga, &numero_registro, tamanhoTabela, numero_teste);
}