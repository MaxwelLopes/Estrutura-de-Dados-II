#ifndef ENCADEIN_H
#define ENCADEIN_H
#include <stdio.h>

struct Registro {
    int indice;
    int codCliente; 
    char nome[100];
    int prox;
    int status; // 0 = liberado e 1 = ocupado
};
typedef struct Registro reg;

void inicializaHash();

void abreArquivo();

void fechaArquivo();

reg criarRegistro(int codCliente, char* nome);

int hash(int codCliente);

void ler();

int busca(int chave, int *indiceLivre, int tipo);

void inserir(reg pessoa);

void remover(int chave);

#endif
