#include <stdio.h>
#include <dirent.h> // Para opendir e readdir
#include <stdlib.h>

int main() {
    // Abrir o diretório (certifique-se de que é um diretório válido)
    DIR *dir = opendir("/home/alunotgn/Documentos/Atividade_1.2SO_Cibelly_Reidner/open_dir_readdir/");
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return 1;
    }

    printf("Conteúdo do diretório:\n");

    // Ler o conteúdo do diretório
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name); // Imprime o nome de cada entrada no diretório
    }

    // Fechar o diretório
    closedir(dir);
    return 0;
}
