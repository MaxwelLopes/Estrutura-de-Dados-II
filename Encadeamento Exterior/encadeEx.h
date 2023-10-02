#ifndef ENCADEEX_H
#define ENCADEEX_H
#include <stdio.h>

struct Registro {
    int indice;
    int codCliente;
    char nome[100];
    int prox;
    int status;
};
typedef struct Registro reg;

int hash(int codCliente);

void ler(FILE* tabelaHash, FILE* clientes);

void inicializaHash(FILE* tabelaHash);

int busca(FILE* tabelaHash, FILE* clientes, int chave);

void inserir(FILE* tabelaHash, FILE* clientes, reg pessoa);

void remover(FILE* tabelaHash, FILE* clientes, int chave);

#endif
