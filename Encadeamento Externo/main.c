#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 7

int indiceCliente = 0;

struct Registro {
    int indice;
    int codCliente;
    char nome[100];
    int prox;
    int status;
};
typedef struct Registro reg;

int hash(int codCliente){    
    return codCliente % M;
}

void ler(FILE* tabelaHash, FILE* clientes){
    int registro_leitura; //auxilixar para ler tabela hash
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < M; i++) {
        if(fread(&registro_leitura, sizeof(int), 1, tabelaHash) != 1) {
            perror("Erro ao ler hash\n");
        }
        printf("%1d %6d\n",i, registro_leitura);
    }
    printf("\n");
    fseek(tabelaHash, 0, SEEK_SET);

    reg aux; //auxlixar pára ler tabela de clientes
    printf("indice     codigo        nome        prox       status\n");
    for(i=0; i<indiceCliente; i++){
        if(fread(&aux, sizeof(reg), 1, clientes) != 1) {
            perror("Erro ao ler tabela de clientes\n");
        }
        printf("%5d     %5d     %10s     %7d     %6d\n",aux.indice, aux.codCliente, aux.nome, aux.prox, aux.status);
    }
    fseek(clientes, 0, SEEK_SET);
}

void inicializaHash(FILE* tabelaHash) {
    int i, valor = -1;
    for(i=0; i<M; i++){
        if (fwrite(&valor, sizeof(int), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
    }
    fseek(tabelaHash, 0, SEEK_SET);
    fflush(tabelaHash);
}

int busca(FILE* tabelaHash, FILE* clientes, int chave){
    int indice = hash(chave);
    fseek(tabelaHash, indice * sizeof(int), SEEK_SET); //pulando o cursor até o indice da hash adequado

    // Lendo valor na hash
    fread(&indice, sizeof(int), 1, tabelaHash);
    
    // caso em que a posição na hash não foi usada
    if(indice == -1){
        return -1;
    }

    // se a posição na hash está vazia
    if(indice != -1){
        //indice = hash(chave); //calculando o indice da hash
        reg registroAtual;
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //pulando o cursor até o registro adequado na lista de clientes
        fread(&registroAtual, sizeof(reg), 1, clientes); //lendo o primeiro cliente do indice da hash
        
        //loop para andar na lista
        while(registroAtual.codCliente != chave){
            if(registroAtual.prox == -1) break; //se achar o ultimo da lista o loop termina
            fseek(clientes, registroAtual.prox * sizeof(reg), SEEK_SET);
            fread(&registroAtual, sizeof(reg), 1, clientes);
        }
        // se o registro atual for difernete da chave (não possui o código de cliente na tabela) retorna o registro atual
        if(registroAtual.codCliente != chave){
            fseek(tabelaHash, 0, SEEK_SET);
            fseek(clientes, 0, SEEK_SET);
            return registroAtual.indice; // retorna o ultimo da lista
        } 
    }
    fseek(tabelaHash, 0, SEEK_SET);
    fseek(clientes, 0, SEEK_SET);
    // se o registro atual for igual a chave retorna -2 (código de cliente encontrado)
    return -2;
}

void inserir(FILE* tabelaHash, FILE* clientes, reg pessoa){
    int indice = busca(tabelaHash, clientes, pessoa.codCliente);
    
    // caso em que já existe o código na tabela de cliente
    if(indice == -2){
        printf("Código de cliente já cadastrado\n");
        exit(0);
    }

    // caso em que a tabela hash está livre
    if(indice == -1){
        int indiceHash = hash(pessoa.codCliente);; 

        //atualizando os campos da pessoa
        pessoa.indice = indiceCliente;  pessoa.status = 0; pessoa.prox = -1;

        //atualizando hash
        fseek(tabelaHash, indiceHash * sizeof(int), SEEK_SET);
        if(fwrite(&indiceCliente, sizeof(int), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
        fseek(tabelaHash, 0, SEEK_SET);
        fflush(tabelaHash);

        //atualizando tabela de clientes
        fseek(clientes, indiceCliente * sizeof(reg), SEEK_SET);
        if (fwrite(&pessoa, sizeof(reg) , 1, clientes) != 1) {  
            perror("Erro ao atualizar tabela de clientes\n");
        }
        indiceCliente++; //atualizando indice da tabela de clientes
        fseek(clientes, 0, SEEK_SET);
        fflush(clientes);
    }
    // caso em que há colisão
    if(indice > -1) {
        reg aux; //auxliar para alterar o registro na tabela de clientes
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //indo até o ultimo registro da lista
        fread(&aux, sizeof(reg), 1, clientes);
        aux.prox = indiceCliente; //atualizando o campo prox do registro atual para o registro novo
        
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //voltando para o registro atual
        //atualizando o registro atual na lista
        fwrite(&aux, sizeof(reg), 1, clientes);

        pessoa.indice = indiceCliente;  pessoa.status = 0; pessoa.prox = -1;

        //atualizando tabela de clientes
        fseek(clientes, indiceCliente * sizeof(reg), SEEK_SET);
        if (fwrite(&pessoa, sizeof(reg) , 1, clientes) != 1) {  
            perror("Erro ao atualizar tabela de clientes\n");
        }
        indiceCliente++; //atualizando indice da tabela de clientes
        fseek(clientes, 0, SEEK_SET);
        fflush(clientes);
    }
}

int main(){
    char* tabHash = "tabHash.dat";
    char* cliente = "cliente.dat";
    
    FILE* tabelaHash = fopen(tabHash,"w+b");
    FILE* clientes = fopen(cliente,"w+b");
    inicializaHash(tabelaHash);

    reg max;
    max.codCliente = 20;
    strcpy(max.nome,"Max");
    max.prox = -1;
    max.status = 0;

    reg luiz;
    luiz.codCliente = 22;
    strcpy(luiz.nome,"Luiz");
    luiz.prox = -1;
    luiz.status = 0;

    reg josue;
    josue.codCliente = 5;
    strcpy(josue.nome,"Josue");
    josue.prox = -1;
    josue.status = 0;

    reg guilherme;
    guilherme.codCliente = 18;
    strcpy(guilherme.nome,"guilherme");
    guilherme.prox = -1;
    guilherme.status = 0;

    

    inserir(tabelaHash, clientes, luiz);
    inserir(tabelaHash, clientes, max);
    inserir(tabelaHash, clientes, josue);
    inserir(tabelaHash, clientes, guilherme);

    reg joao;
    joao.codCliente = 49;
    strcpy(joao.nome,"Joao");
    joao.prox = -1;
    joao.status = 0;

    reg maria;
    maria.codCliente = 59;
    strcpy(maria.nome,"Maria");
    maria.prox = -1;
    maria.status = 0;

    reg ana;
    ana.codCliente = 103;
    strcpy(ana.nome,"Ana");
    ana.prox = -1;
    ana.status = 0;

    reg jose;
    jose.codCliente = 3;
    strcpy(jose.nome,"Jose");
    jose.prox = -1;
    jose.status = 0;

    reg carla;
    carla.codCliente = 51;
    strcpy(carla.nome,"Carla");
    carla.prox = -1;
    carla.status = 0;

    reg bia;
    bia.codCliente = 87;
    strcpy(bia.nome,"Bia");
    bia.prox = -1;
    bia.status = 0;

    inserir(tabelaHash, clientes, joao);
    inserir(tabelaHash, clientes, maria);
    inserir(tabelaHash, clientes, ana);
    inserir(tabelaHash, clientes, jose);
    inserir(tabelaHash, clientes, carla);
    inserir(tabelaHash, clientes, bia);

    ler(tabelaHash, clientes);

    fclose(tabelaHash);
    fclose(clientes);  

    return 0;
}