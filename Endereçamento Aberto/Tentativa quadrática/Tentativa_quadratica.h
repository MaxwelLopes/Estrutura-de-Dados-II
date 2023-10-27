#ifndef ENCADEIN_H
#define ENCADEIN_H
#include <stdio.h>

#define M 10

struct Cliente {
    int codCliente;
    char nome[100];
};

typedef struct Cliente cliente;

typedef cliente *Hash;

int hash_linha(int x);

int hash(int x, int k);

int busca(Hash *tab_hash, int x, int *achou);

Hash aloca(int codCliente, char *nome);

void inserir(Hash *tab_hash, int codCliente, char *nome);

void remover(Hash *tab_hash, int x);

void imprimir(Hash *tab_hash);


#endif
