#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 7


int indiceCliente = 0;

struct Registro {
    int codCliente;
    char nome[100];
    int prox;
    int status;
};

typedef struct Registro reg;

int hash(int codCliente){    
    return codCliente % M;
}

void inicializaHash(char* tabHash) {
    FILE* tabelaHash = fopen(tabHash, "a+b");
    int valor[M];
    for (int i = 0; i < M; i++) {
        valor[i] = -1;
    }
    if (fwrite(valor, sizeof(int), M, tabelaHash) != M) {  
        perror("Erro ao escrever no arquivo");
    }
    fclose(tabelaHash);
}

void ler(char* tabHash){
    FILE* arquivo = fopen(tabHash, "a+b");
    int registro_leitura[M];
    if(fread(registro_leitura, sizeof(int), M, arquivo) != M) {
        perror("Erro ao ler do arquivo");
    }
    int i;
    for (i = 0; i < M; i++) {
        printf("%d\n", registro_leitura[i]);
    }
    fclose(arquivo);
}

int busca(char* tabHash, char* cliente, int chave){
    int indice;
    FILE* tabelaHash = fopen(tabHash, "a+b");

    // EndereçoReg(i) = (i – 1) * tamanhoReg 
    int enderecoHash = hash(chave) * sizeof(int);
    
    fseek(tabelaHash, enderecoHash, SEEK_SET);

    // Leia um byte a partir da posição desejada
    fread(&indice, sizeof(int), 1, tabelaHash);

    // se a posição na hash está vazia
    if(indice == -1){
        printf("posição vazia\n");
        return indice;
    }

    // se a posição na hash não está vazia(houve colisão)
    if(indice != -1){
        FILE* clientes = fopen(cliente, "a+b");

        fseek(clientes, indice, SEEK_SET);

        reg registroAtual;
        fread(&registroAtual, sizeof(reg), 1, clientes);
        
        while(registroAtual.codCliente != chave){
            fseek(clientes, registroAtual.prox, SEEK_SET);
            fread(&registroAtual, sizeof(reg), 1, clientes);

            if(registroAtual.prox == -1) break;
        }
        
        fclose(clientes);
        if(registroAtual.codCliente == chave) return chave;
    }
    
    fclose(tabelaHash);
    return -1;
}

void inserir(char* tabHash, char* cliente, reg pessoa){
    int indice = hash(pessoa.codCliente); 
    int buscaRetorno = busca(tabHash, cliente, indice);

    //valor já está na hash
    if(buscaRetorno != -1){
        printf("já tem!! :C\n");
        exit(1);
    }
    FILE* tabelaHash = fopen(tabHash, "a+b");
    FILE* clientes = fopen(cliente, "a+b");
    
    //Primeira inserção em uma posição da hash 
    if(buscaRetorno == -1){
        pessoa.prox = -1;
        pessoa.status = 0;
        fseek(clientes, indiceCliente * sizeof(reg), SEEK_SET);
        fseek(tabelaHash, indice * sizeof(int), SEEK_SET);
        if (fwrite(&pessoa, sizeof(reg), 1, clientes) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
        if (fwrite(&buscaRetorno, sizeof(reg), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
        
    }
}//ueuwuwuwuwuwuwuwuw

typedef struct Registro reg;

int main(){
    char* tabHash = "tabHash.dat";
    char* cliente = "cliente.dat";
    
    FILE* tabelaHash = fopen(tabHash,"w+b");
    FILE* clientes = fopen(cliente,"w+b");
    fclose(tabelaHash);
    fclose(clientes);
    
    reg luiz;
    luiz.codCliente = 2;
    strcpy(luiz.nome,"Luiz");
    luiz.prox = -1;
    luiz.status = 0;

    // reg josue;
    // luiz.codCliente = 10;
    // strcpy(luiz.nome,"Josue");
    // luiz.prox = -1;
    // luiz.status = 0;

    // reg max;
    // luiz.codCliente = 15;
    // strcpy(luiz.nome,"Max");
    // luiz.prox = -1;
    // luiz.status = 0;

    // reg hugo;
    // luiz.codCliente = 15;
    // strcpy(luiz.nome,"Hugo");
    // luiz.prox = -1;
    // luiz.status = 0;



    inicializaHash(tabHash);
    inserir(tabHash,cliente,luiz);
    busca(tabHash, cliente, 2);
    
    ler(tabHash);

    return 0;
}