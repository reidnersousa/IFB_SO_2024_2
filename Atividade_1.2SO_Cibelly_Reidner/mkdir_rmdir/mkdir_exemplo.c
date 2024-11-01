#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h> // Inclua esta linha para usar printf e perror

int main() {
    int result = mkdir("novo_diretorio", 0777); // 0777 define permissões de leitura, escrita e execução
    if (result == 0) {
        printf("Diretório criado com sucesso.\n");
    } else {
        perror("Erro ao criar diretório");
    }
    return 0;
}
