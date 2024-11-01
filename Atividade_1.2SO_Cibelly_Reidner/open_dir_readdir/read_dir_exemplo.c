#include <stdio.h>
#include <dirent.h> // Para opendir e readdir
#include <stdlib.h>

// Função para ler um diretório
void ler_diretorio(const char *caminho) {
    // Abrir o diretório
    DIR *dir = opendir(caminho);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    printf("Conteúdo do diretório '%s':\n", caminho);

    // Ler o conteúdo do diretório
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name); // Imprime o nome de cada entrada no diretório
    }

    // Fechar o diretório
    closedir(dir);
}

int main() {
    const char *caminho_diretorio = "/home/alunotgn/Documentos/Atividade_1.2SO_Cibelly_Reidner/open_dir_readdir/";
    ler_diretorio(caminho_diretorio); // Chama a função para ler o diretório
    return 0;
}
