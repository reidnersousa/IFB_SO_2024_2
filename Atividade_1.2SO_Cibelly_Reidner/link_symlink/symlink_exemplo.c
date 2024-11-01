#include <stdio.h>
#include <unistd.h>

int main() {
    const char *arquivo_original = "arquivo.txt";
    const char *link_simbolico = "link_simbolico.txt";

    // Criar um link simbólico
    if (symlink(arquivo_original, link_simbolico) == -1) {
        perror("Erro ao criar link simbólico");
        return 1;
    }

    printf("Link simbólico '%s' criado para '%s'.\n", link_simbolico, arquivo_original);
    return 0;
}
