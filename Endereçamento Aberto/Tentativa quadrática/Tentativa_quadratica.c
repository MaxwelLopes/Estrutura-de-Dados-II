#include <stdio.h>
#include <stdlib.h>
#include "Tentativa_Quadratica.h"
#define INSERCAO 1

void inicializa(Hash *tab_hash, int tamanhoTabela){
    int i;

    for(i=0; i<tamanhoTabela; i++){
        tab_hash[i] = NULL;
    }
}

int hash_linha(int x, int tamanhoTabela){
    return x % tamanhoTabela;
}

int hash(int x, int k, int tamanhoTabela){
    int c1 = 0, c2 = 1;
    return (hash_linha(x,tamanhoTabela) + c1*k + c2*k*k) % tamanhoTabela;

    // if(k == 0){
    //     return hash_linha(x, tamanhoTabela);
    // }
    // return (hash(x,k-1,tamanhoTabela) + k) % tamanhoTabela;
}

int busca(Hash *tab_hash, int tamanhoTabela, int x, int *achou, int *colisao){
    *achou = 0;
    int endereco = -1;
    int pos_livre = -1;
    int k = 0;

    //loop para percorrer a hash
    while(k < tamanhoTabela){
        endereco = hash(x, k, tamanhoTabela);

        if(tab_hash[endereco] != NULL && pos_livre == -1){
            *colisao = *colisao + 1;
        }

        // caso em que encontrou a chave
        if(tab_hash[endereco] != NULL && tab_hash[endereco]->codCliente == x){
            *achou = 1;
            *colisao = *colisao - 1;
            k = tamanhoTabela; // forçar saída do loop
        }
        // caso em que não enctou a chave
        else{
            // caso em que encontrou um endereço livre
            if(tab_hash[endereco] == NULL){
                // guardando o endereço livre caso ele seja o primeiro
                if(pos_livre == -1){
                    pos_livre = endereco;
                }
            }
            k++; //continua a procura
        }
    }
    //printf("\n%d colisões\n",*colisao);
    // Caso em que a chave foi encontrada na hash
    if(*achou){
        return endereco;
    }
    // caso em que o a chave não foi encontrada
    // retorna o primeiro endereço livre que é encontrado ou -1 caso não tenha endereços livres
    else{
        return pos_livre;
    }
}

Hash aloca(int codCliente){

    Hash endereco = (Hash) malloc(sizeof(cliente));
    
    endereco->codCliente = codCliente;
    
    return endereco;
}

void inserir(Hash *tab_hash, int codCliente, int *numRegistro, int *colisao, int tamanhoTabela){
    int achou; // flag para saber se a chave do cliente já existe na tabela hash
    int endereco = busca(tab_hash, tamanhoTabela, codCliente, &achou, colisao);
    
    // caso em que o codigo do cliente não existe na tabela hash e o registro pode ser inserido
    if(!achou){
        // caso em que a função de busca encontrou uma posição livre na tabela hash
        if(endereco != -1){
            tab_hash[endereco] = aloca(codCliente);
            *numRegistro = *numRegistro + 1;
        }
        // caso em que não foi encontrado endereço livre da tabela hash
        else{
            //printf("ERRO: Tabela cheia. Registro %d não foi inserido!\n",codCliente);
        }
    }

    // caso em que o código do cliente foi encontrado na tabela Hash
    else{
        //printf("ERRO: Código de cliente já existe. Registro %d não foi inserido!\n",codCliente);

    }
}

void remover(Hash *tab_hash, int tamanhoTabela, int x){
    int achou;
    int lixo;
    int endereco = busca(tab_hash, tamanhoTabela, x, &achou, &lixo);

    if(achou){
        tab_hash[endereco] = NULL;
        free(tab_hash[endereco]);
    }
    else{
        //printf("ERRO: Códido de cliente não encontrado!\n");
    }
}

void imprimir(Hash *tab_hash, int tamanhoTabela){
    int i;
    printf("\nTabela Hash:\n");
    printf("indice     codigo\n");
    for(i = 0; i < tamanhoTabela; i++){
        if(tab_hash[i] == NULL){
            printf("%4d %10s \n",i,"-");
        }
        else{
            printf("%4d %10d\n",i,tab_hash[i]->codCliente);
        }
    }
}