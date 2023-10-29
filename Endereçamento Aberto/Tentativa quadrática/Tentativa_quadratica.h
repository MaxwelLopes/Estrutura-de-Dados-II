#ifndef ENCADEIN_H
#define ENCADEIN_H
#include <stdio.h>

struct Cliente {
    int codCliente;
};

typedef struct Cliente cliente;

typedef cliente *Hash;

int hash_linha(int x, int tamanhoTabela);

int hash(int x, int tamanhoTabela ,int k);

int busca(Hash *tab_hash, int tamanhoTabela, int x, int *achou, int *colisao);

Hash aloca(int codCliente);

void inserir(Hash *tab_hash, int codCliente, int *numRegistro, int *colisao, int tamanhoTabela);

void remover(Hash *tab_hash, int tamanhoTabela, int x);

void imprimir(Hash *tab_hash, int tamanhoTabela);

#endif
