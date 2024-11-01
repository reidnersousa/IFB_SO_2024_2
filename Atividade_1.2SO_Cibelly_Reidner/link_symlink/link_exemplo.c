#include <stdio.h>
#include <unistd.h>

int main() {
    const char *arquivo_original = "arquivo.txt";
    const char *link_fisico = "link_fisico.txt";

    // Criar um link físico
    if (link(arquivo_original, link_fisico) == -1) {
        perror("Erro ao criar link físico");
        return 1;
    }

    printf("Link físico '%s' criado para '%s'.\n", link_fisico, arquivo_original);
    return 0;
}