#include <stdio.h>
#include <string.h>

struct Registro {
    int codCliente;
    char nome[100];
};

typedef struct Registro reg;

void registra(reg* registro, int m){
    int i;
    for(i=0; i<m; i++){
        strcpy(registro[i].nome, "João");
        registro[i].codCliente = i;
    }
}


int main() {

    int m = 5;
    reg registro[m];

    reg registro_leitura[m];

    registra(registro,m);

    // Nome do arquivo que você deseja criar ou abrir
    const char *nome_arquivo = "Luiz.bin";

    // Abrir o arquivo em modo de leitura e escrita binária ("r+b")
    FILE *arquivo = fopen(nome_arquivo, "w+b");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Escrever os dados no arquivo
    size_t tamanho_dados = sizeof(registro[0]);  //tamanho de um registro
    size_t num_elementos = sizeof(registro) / tamanho_dados;

    if (fwrite(registro, tamanho_dados, num_elementos, arquivo) != num_elementos) {
        perror("Erro ao escrever no arquivo");
        return 1;
    }

    fclose(arquivo);

    arquivo = fopen(nome_arquivo, "a+b");


    if (fread(registro_leitura, sizeof(reg), num_elementos, arquivo) != num_elementos) {
        perror("Erro ao ler do arquivo");
        fclose(arquivo);
        return 1;
    }

    // Fechar o arquivo
    fclose(arquivo);

    printf("Dados escritos com sucesso em %s\n", nome_arquivo);
    
    int i;
    for(i=0; i<m; i++){
         printf("Nome: %s\nCodigo: %d\n\n", registro_leitura[i].nome, registro_leitura[i].codCliente);
    }
          
    return 0;
}
