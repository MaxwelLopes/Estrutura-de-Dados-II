#ifndef ENCADEIN_H
#define ENCADEIN_H
#include <stdio.h>
#include <stdbool.h>

struct Cliente {
    int codCliente;
};

typedef struct Cliente cliente;

typedef cliente *Hash;

bool is_prime(int n);

int find_previous_prime(int X);

int hash_linha(int x, int tamanhoTabela);

int hash_linha_linha(int x, int PRIMO);

int hash(int x, int k, int tamanhoTabela, int PRIMO);

int busca(Hash *tab_hash, int tamanhoTabela, int x, int *achou, int *colisao, int PRIMO);

Hash aloca(int codCliente);

void inserir(Hash *tab_hash, int codCliente, int *numRegistro, int *colisao, int tamanhoTabela, int PRIMO);

void remover(Hash *tab_hash, int tamanhoTabela, int x, int PRIMO);

void imprimir(Hash *tab_hash, int tamanhoTabela);

#endif
