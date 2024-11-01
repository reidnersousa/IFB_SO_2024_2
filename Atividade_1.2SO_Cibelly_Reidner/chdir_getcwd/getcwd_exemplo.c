#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    // Obter o diretório de trabalho atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretório de trabalho atual: %s\n", cwd);
    } else {
        perror("Erro ao obter o diretório de trabalho atual");
        return 1;
    }

    return 0;
}
