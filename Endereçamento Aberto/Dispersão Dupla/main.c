#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dispersao_Dupla.c"
#include "benchmark.c"

int main(){
    int tamanhoTabela = 10000;
    int PRIMO =  find_previous_prime(tamanhoTabela);
    Hash tab_hash[tamanhoTabela];
    float fator_carga = 0.9;
    int numero_registro;
    int numero_teste = 10;
    
    inicializa(tab_hash, tamanhoTabela);
    benchmarkInsercao(tab_hash, fator_carga, &numero_registro, tamanhoTabela, numero_teste, PRIMO);
}