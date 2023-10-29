#include <stdio.h>
#include <stdlib.h>
#include "Dispersao_Dupla.h"

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int find_previous_prime(int X) {
    if (X <= 2) {
        // Não há primos menores que 2.
        return -1; // Indicar que não há primo anterior.
    }
    if (X == 3) {
        // O único primo anterior a 3 é 2.
        return 2;
    }
    if (X % 2 == 0) {
        X--; // Se X for par, tornamos X ímpar.
    } else {
        X -= 2; // Se X for ímpar, subtrair 2 para torná-lo par.
    }

    while (X > 1) {
        if (is_prime(X)) {
            return X;
        }
        X -= 2; // Teste apenas números ímpares.
    }
    return -1; // Se não for encontrado, retornar -1.
}

void inicializa(Hash *tab_hash, int tamanhoTabela){
    int i;

    for(i=0; i<tamanhoTabela; i++){
        tab_hash[i] = NULL;
    }
}

int hash_linha(int x, int tamanhoTabela){
    //printf("hash' = %d\n", x % M);
    return x % tamanhoTabela;
}

int hash_linha_linha(int x, int PRIMO){
    //printf("hash'' = %d\n", 7 - (x % 7));
    return PRIMO - (x % PRIMO);
}

int hash(int x, int k, int tamanhoTabela, int PRIMO){
    return (hash_linha(x,tamanhoTabela) + k * hash_linha_linha(x,PRIMO)) % tamanhoTabela;
}

int busca(Hash *tab_hash, int tamanhoTabela, int x, int *achou, int *colisao, int PRIMO){
    *achou = 0;
    int endereco = -1;
    int pos_livre = -1;
    int k = 0;

    //loop para percorrer a hash
    while(k < tamanhoTabela){
        endereco = hash(x, k, tamanhoTabela, PRIMO);

        if(tab_hash[endereco] != NULL && pos_livre == -1){
            *colisao = *colisao + 1;
        }

        // caso em que encontrou a chave
        if(tab_hash[endereco] != NULL && tab_hash[endereco]->codCliente == x ){
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

void inserir(Hash *tab_hash, int codCliente, int *numRegistro, int *colisao, int tamanhoTabela, int PRIMO){
    int achou; // flag para saber se a chave do cliente já existe na tabela hash
    int endereco = busca(tab_hash, tamanhoTabela, codCliente, &achou, colisao, PRIMO);
    
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

void remover(Hash *tab_hash, int tamanhoTabela, int x, int PRIMO){
    int achou;
    int lixo;
    int endereco = busca(tab_hash, tamanhoTabela, x, &achou, &lixo, PRIMO);

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