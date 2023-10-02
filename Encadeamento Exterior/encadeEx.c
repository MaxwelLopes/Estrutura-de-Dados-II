#include "EncadeEx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 7

int indiceCliente = 0;

FILE* tabelaHash;
FILE* clientes; 

void inicializaHash() {
    int i, valor = -1;
    for(i=0; i<M; i++){
        if (fwrite(&valor, sizeof(int), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
    }
    fseek(tabelaHash, 0, SEEK_SET);
    fflush(tabelaHash);
}

void abreArquivo(){
    tabelaHash = fopen("tabHash.dat","w+b");
    clientes = fopen("cliente.dat","w+b");
    inicializaHash(tabelaHash);
}

void fechaArquivo(){
    fclose(tabelaHash);
    fclose(clientes);
}

int hash(int codCliente){    
    return codCliente % M;
}

reg criarRegistro(int codCliente, char* nome){
    reg registro;
    registro.codCliente = codCliente;
    strcpy(registro.nome,nome);
    registro.prox = -1;
    registro.status = 0;
    return registro;
}

void ler(){
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

int busca(int chave, int tipo){ //tipo == 1 busca para remoção
    int indice = hash(chave);
    reg registroAtual;
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
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //pulando o cursor até o registro adequado na lista de clientes
        fread(&registroAtual, sizeof(reg), 1, clientes); //lendo o primeiro cliente do indice da hash
        
        //loop para andar na lista
        while(registroAtual.codCliente != chave){
            if(registroAtual.prox == -1 || registroAtual.status == 1) break; //se achar o ultimo da lista o loop termina
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
    if(tipo == 1){
        return registroAtual.indice;
    }
    return -2;
}

void inserir(reg registro){
    int indice = busca(registro.codCliente, 0); 
    
    // caso em que já existe o código na tabela de cliente
    if(indice == -2){
        printf("Código de cliente já cadastrado\n");
        exit(0);
    }

    // caso em que a tabela hash está livre
    if(indice == -1){
        int indiceHash = hash(registro.codCliente);; 

        //atualizando os campos da registro
        registro.indice = indiceCliente;  registro.status = 0; registro.prox = -1;

        //atualizando hash
        fseek(tabelaHash, indiceHash * sizeof(int), SEEK_SET);
        if(fwrite(&indiceCliente, sizeof(int), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
        fseek(tabelaHash, 0, SEEK_SET);
        fflush(tabelaHash);

        //atualizando tabela de clientes
        fseek(clientes, indiceCliente * sizeof(reg), SEEK_SET);
        if (fwrite(&registro, sizeof(reg) , 1, clientes) != 1) {  
            perror("Erro ao atualizar tabela de clientes\n");
        }
        indiceCliente++; //atualizando indice da tabela de clientes
        fseek(clientes, 0, SEEK_SET);
        fflush(clientes);
    }
    // caso em que há colisão
    reg aux; //auxliar para alterar o registro na tabela de clientes
    fseek(clientes, indice * sizeof(reg), SEEK_SET); //indo até o ultimo registro da lista
    fread(&aux, sizeof(reg), 1, clientes);
    // caso em que a lista está toda ocupada
    if(indice > -1 && aux.status != 1) {
        
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //indo até o ultimo registro da lista
        fread(&aux, sizeof(reg), 1, clientes);
        aux.prox = indiceCliente; //atualizando o campo prox do registro atual para o registro novo
        
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //voltando para o registro atual
        //atualizando o registro atual na lista
        fwrite(&aux, sizeof(reg), 1, clientes);

        registro.indice = indiceCliente;  registro.status = 0; registro.prox = -1;

        //atualizando tabela de clientes
        fseek(clientes, indiceCliente * sizeof(reg), SEEK_SET);
        if (fwrite(&registro, sizeof(reg) , 1, clientes) != 1) {  
            perror("Erro ao atualizar tabela de clientes\n");
        }
        indiceCliente++; //atualizando indice da tabela de clientes
        fseek(clientes, 0, SEEK_SET);
        fflush(clientes);
    }
    // caso em que a lista há espaço na lista
    else if(aux.status == 1){
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //indo até o ultimo registro da lista
        fread(&aux, sizeof(reg), 1, clientes);

        // atualizando registro
        registro.prox = aux.prox;
        registro.indice = aux.indice;
        registro.status = 0;
    
        
        fseek(clientes, indice * sizeof(reg), SEEK_SET); //voltando para o registro atual
        //atualizando o registro atual na lista
        fwrite(&registro, sizeof(reg), 1, clientes);

        
        fseek(clientes, 0, SEEK_SET);
        fflush(clientes);
    }
}

void remover(int chave){
    int indice = busca(chave, 1);
    reg aux;

    fseek(clientes, indice * sizeof(reg), SEEK_SET); // pulando o curso até o registro desejado 
    fread(&aux, sizeof(reg) , 1, clientes);  // lendo registro 
    
    // excluindo registro
    aux.status = 1;
    aux.codCliente = -1;
    strcpy(aux.nome, "-");

    fseek(clientes, indice * sizeof(reg), SEEK_SET); // pulando o curso até o registro desejado 
    fwrite(&aux, sizeof(reg), 1, clientes);  // atualizando tabela de clientes

    fseek(clientes, 0, SEEK_SET);
    fflush(clientes);
}