#include <stdio.h>
#include <unistd.h>

int main() {
    const char *novo_diretorio = "/home/alunotgn";

    // Mudar o diretório de trabalho
    if (chdir(novo_diretorio) != 0) {
        perror("Erro ao mudar o diretório");
        return 1;
    }

    printf("Diretório de trabalho mudado para '%s'.\n", novo_diretorio);
    return 0;
}
