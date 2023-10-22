#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encadeIn.h"
#define M 7 
#define INSERCAO 1

int indiceCliente = 0;

FILE* tabelaHash;

void inicializaHash() {
    int i;
    reg valor = criarRegistro(-1, "-");
    for(i=0; i<M; i++){
        valor.indice = i;
        valor.status = 1;
        if (fwrite(&valor, sizeof(reg), 1, tabelaHash) != 1) {  
            perror("Erro ao escrever no arquivo");
        }
    }
    fseek(tabelaHash, 0, SEEK_SET);
    fflush(tabelaHash);
}

reg criarRegistro(int codCliente, char* nome){
    reg registro;
    registro.codCliente = codCliente;
    strcpy(registro.nome,nome);
    registro.prox = -1;
    registro.status = 0;
    return registro;
}

void abreArquivo(){
    tabelaHash = fopen("tabHash.dat","w+b");
    inicializaHash();
}

void fechaArquivo(){
    fclose(tabelaHash);
}

int hash(int codCliente){    
    return codCliente % M;
}

void ler(){
    reg registro_leitura; //auxilixar para ler tabela hash

    printf("\nTabela Hash:\n");
    printf("indice     codigo        nome        prox       status\n");

    fseek(tabelaHash, 0, SEEK_SET);
    while(fread(&registro_leitura, sizeof(reg), 1, tabelaHash) == 1){
        printf("%5d     %5d     %10s     %7d     %6d\n",registro_leitura.indice, registro_leitura.codCliente, registro_leitura.nome, registro_leitura.prox, registro_leitura.status);
    }
    printf("\n");
}

int busca(int chave, int *indiceLivre, int tipo){
    int indice = hash(chave);
    *indiceLivre = -1;
    reg registro_leitura;
    reg aux;

    fseek(tabelaHash, indice * sizeof(reg), SEEK_SET);//pulando o cursor até o indice da hash adequado
    if(fread(&registro_leitura, sizeof(reg), 1, tabelaHash) != 1){
        perror("Erro ao ler arquivo");
    }

    // caso em que a posição na hash não foi usada
    if(registro_leitura.codCliente == -1){
        return -1;
    }

    indice = registro_leitura.indice;
    
    // caso em que a posição da hash está ocupada
    fseek(tabelaHash, indice * sizeof(reg), SEEK_SET); // pulando o cursor até o indice da hash adequado
    // if(fread(&registro_leitura, sizeof(reg), 1, tabelaHash) != 1){
    //     perror("Erro ao ler arquivo");
    // }
    
    // loop para andar na lista
    while(registro_leitura.codCliente != chave){
        
        // verificando se a posição está disponível para uso futuro
        if(registro_leitura.status == 1){
            *indiceLivre = registro_leitura.indice;
        }

        // quando chega no final da lista o loop termina
        if(registro_leitura.prox == -1){
            break;
        } 

        //pegando o proximo registro da lista para continuar o loop
        fseek(tabelaHash, registro_leitura.prox * sizeof(reg), SEEK_SET);
        if(fread(&registro_leitura, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao ler arquivo");
        }
    }

    // caso para inserção
    // Caso em que a chave pode ser inserida
    if((tipo && (registro_leitura.codCliente != chave)) || registro_leitura.status){
        int i;

        // caso em que não foi encontrado um espaço na hash
        if(*indiceLivre == -1){
            fseek(tabelaHash, 0, SEEK_SET);
            // o loop percorre a hash inteira até encontrar um espaço livre
            for(i=0; i<M; i++){
                if(fread(&aux, sizeof(reg), 1, tabelaHash) != 1){
                    perror("Erro ao ler arquivo");
                }

                // o loop termina quando acha um espaço livre
                if(aux.codCliente == -1 || aux.status == 1){
                    *indiceLivre = aux.indice;
                    break;
                } 
            }

            // caso em que não foi encontrado espaço livre na hash
            if(i==M){  
                return -3;
            } 
        }
        // caso em que foi encontrado um espaço livre enquanto percorria a lista
        return registro_leitura.indice;
    }

    // caso de inserção onde já existe a chave na hash
    if(tipo && registro_leitura.codCliente == chave){
        return -2;
    }
    // caso para não inserção
    // retorando o indice da hash em que a chave se encontra
    return registro_leitura.indice;
}

void inserir(reg registro){
    int indiceLivre;
    int indice = busca(registro.codCliente, &indiceLivre, INSERCAO);
    reg registro_anterior;
    reg registro_novo;

    // caso em que a chave já existe na hash
    if(indice == -2){
        printf("\nJÁ TEM! Registro %d não inserido!\n",registro.codCliente);
        return;
    }

    // caso em que a hash está cheia
    if(indice == -3){
        printf("\nTÁ CHEIO! Registro %d não inserido!\n",registro.codCliente);
        return;
    }
    
    // caso em que o espaço na hash não fui utilizado
    if(indice == -1){
        // o registro é inserido diretamente na hash
        indiceLivre = hash(registro.codCliente);
        fseek(tabelaHash, indiceLivre * sizeof(reg), SEEK_SET);
        if(fread(&registro_novo, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao ler no arquivo");
        }

        registro.indice = registro_novo.indice; registro.prox = registro_novo.prox;
        fseek(tabelaHash, indiceLivre * sizeof(reg), SEEK_SET);
        if(fwrite(&registro, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao escrever no arquivo");
        }
        fflush(tabelaHash);
    }

    // caso em que há colisão
    // nesse caso a função de busca retorna o registro que vai apontar para o novo registro e atualiza o ponteiro com o indice em que o novo registro deve ficar
    if(indice != -1){
        // indo até o registro anterior para atulizar o campo prox

        // escrevendo o indece novo na hash
        fseek(tabelaHash, indiceLivre * sizeof(reg), SEEK_SET);
        if(fread(&registro_anterior, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao ler no arquivo");
        }

        fseek(tabelaHash, indice * sizeof(reg), SEEK_SET);
        if(fread(&registro_novo, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao ler no arquivo");
        }

        if(registro_anterior.prox == -1){
            registro_novo.prox = indiceLivre;
        }

        fseek(tabelaHash, indice * sizeof(reg), SEEK_SET);
        if(fwrite(&registro_novo, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao escrever no arquivo");
        }


        registro.indice = registro_anterior.indice; 
        registro.prox = registro_anterior.prox;

        if(registro_anterior.prox == indiceLivre){
            registro.prox = -1;
        }

        fseek(tabelaHash, indiceLivre * sizeof(reg), SEEK_SET);
        if(fwrite(&registro, sizeof(reg), 1, tabelaHash) != 1){
            perror("Erro ao escrever no arquivo");
        }
        fflush(tabelaHash);
    }
}

void remover(int chave){
    int null;
    int indice = busca(chave, &null, !INSERCAO);
    // a função de busca para !inserção retorna o indice da hash em que a cheve se encontra

    // caso em que a função encontra o indice
    if(indice > -1){
        reg registro_leitura;
        
        // indo até o registro 
        fseek(tabelaHash, indice * sizeof(reg), SEEK_SET);
        if(fread(&registro_leitura, sizeof(reg), 1, tabelaHash) != 1){
            printf("Erro ao ler aqruivo\n");
        }

        // removendo registro da hash
        strcpy(registro_leitura.nome, "-");
        registro_leitura.status = 1;
        fseek(tabelaHash, indice * sizeof(reg), SEEK_SET);
        if(fwrite(&registro_leitura, sizeof(reg), 1, tabelaHash) != 1){
            printf("Erro ao ler aqruivo\n");
        }
    }
    // caso em que não foi encontrado a chave na hash
    else{
        printf("NÂO TEM! Registro %d não removido\n",chave);
    }
}