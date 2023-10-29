#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"
#include <sys/time.h>

void benchmarkInsercao(Hash *tabela, float fatorCarga, int *numRegistros, int tamanhoTabela, int numeroTeste){
    *numRegistros = 0;
    int colisao = 0;
    double tempo_inicio, tempo_final;
    double tempo_total;
    int chave, escolhaAleatoria, insercao = 0, remocao = 0;


    int media_colisao = 0;
    double media_tempo = 0;
    int i;

    for(i = 0; i < numeroTeste; i++){
        *numRegistros = 0;
        colisao = 0;
        insercao = 0;
        remocao = 0;
        
        inicializa(tabela, tamanhoTabela);
    
        //printf("Teste %d:\n",i+1);
        
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        long seed = (long) (current_time.tv_sec * 1000000) + current_time.tv_usec;
        srand(seed);

        tempo_inicio = clock();
        
        while((((float)*numRegistros)/(float)tamanhoTabela) < fatorCarga){
            
            chave = rand(); 
            //printf("\nchave: %d\n",chave);
            
            escolhaAleatoria = rand() % 2;
            
            if(escolhaAleatoria){
                inserir(tabela, chave, numRegistros, &colisao, tamanhoTabela);
                insercao++;
            }
            else{
                remover(tabela, tamanhoTabela, numRegistros, chave);
                remocao++;
            }
        }
        
        tempo_final = clock();

        tempo_total = (double)(tempo_final - tempo_inicio) / CLOCKS_PER_SEC;

        // printf("\nRESULTADO:\n");
        // printf("Tentativas de inserção: %d\n",insercao);
        // printf("Tentativas de remoção: %d\n",remocao);
        // printf("Número de Colisões: %d\n", colisao);
        // printf("Tempo de execução: %.10lf\n", tempo_total);
        // printf("\n");        
        
        media_colisao += colisao;
        media_tempo += tempo_total;
        //imprimir(tabela, tamanhoTabela);
        
    }
    printf("\nMédia Colisão: %d\n",media_colisao/numeroTeste);
    printf("Média Tempo: %lf\n",media_tempo/numeroTeste);
}