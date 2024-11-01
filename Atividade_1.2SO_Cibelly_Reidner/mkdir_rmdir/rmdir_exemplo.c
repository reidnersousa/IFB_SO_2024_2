#include <stdio.h>
#include <unistd.h> // Para usar a função rmdir
#include <stdio.h>
int main() {
    int result = rmdir("novo_diretorio");

    if (result == 0) {
        printf("Diretório removido com sucesso.\n");
    } else {
        perror("Erro ao remover diretório");
    }
    
    return 0;
}
