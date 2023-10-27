#include <stdio.h>
#include <stdlib.h>
#include "Tentativa_quadratica.h"

void inicializa(Hash *tab_hash){
    int i;

    for(i=0; i<M; i++){
        tab_hash[i] = NULL;
    }
}

int hash_linha(int x){
    return x % M;
}

int hash(int x, int k){
    // int c1 = 1, c2 = 2;
    // return (hash_linha(x) + c1*k + c2*k*k) % M;

    if(k == 0){
        return hash_linha(x);
    }
    return (hash(x,k-1) + k) % M;
}

int busca(Hash *tab_hash, int x, int *achou){
    *achou = 0;
    int endereco = -1;
    int pos_livre = -1;
    int k = 0;
    int colisao = 0;

    //loop para percorrer a hash
    while(k < M){
        endereco = hash(x, k);

        if(tab_hash[endereco] != NULL){
            colisao++;
        }

        // caso em que encontrou a chave
        if(tab_hash[endereco] != NULL && tab_hash[endereco]->codCliente == x){
            *achou = 1;
            k = M; // forçar saída do loop
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
    printf("\n%d colisões\n",colisao);
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

Hash aloca(int codCliente, char *nome){

    Hash endereco = (Hash) malloc(sizeof(cliente));
    
    endereco->codCliente = codCliente;
    strcpy(endereco->nome, nome);
    
    
    return endereco;
}

void inserir(Hash *tab_hash, int codCliente, char *nome){
    int achou; // flag para saber se a chave do cliente já existe na tabela hash
    int endereco = busca(tab_hash, codCliente, &achou); 
    
    // caso em que o codigo do cliente não existe na tabela hash e o registro pode ser inserido
    if(!achou){
        // caso em que a função de busca encontrou uma posição livre na tabela hash
        if(endereco != -1){
            tab_hash[endereco] = aloca(codCliente, nome);
        }
        // caso em que não foi encontrado endereço livre da tabela hash
        else{
            printf("ERRO: Tabela cheia. Registro %d não foi inserido!\n",codCliente);
        }
    }

    // caso em que o código do cliente foi encontrado na tabela Hash
    else{
        printf("ERRO: Código de cliente já existe. Registro %d não foi inserido!\n",codCliente);
    }
}

void remover(Hash *tab_hash, int x){
    int achou;
    int endereco = busca(tab_hash, x, &achou);

    if(achou){
        free(tab_hash[endereco]);
        tab_hash[endereco] = NULL;
    }
    else{
        printf("ERRO: Códido de cliente não encontrado!\n");
    }
}

void imprimir(Hash *tab_hash){
    int i;
    printf("\nTabela Hash:\n");
    printf("indice     codigo        nome\n");
    for(i = 0; i < M; i++){
        if(tab_hash[i] == NULL){
            printf("%4d %10s %12s\n",i,"-","-");
        }
        else{
            printf("%4d %10d %13s\n",i,tab_hash[i]->codCliente,tab_hash[i]->nome);
        }
    }
}