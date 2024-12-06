#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h> // Para sleep()

#define MAX_THREADS 10
#define MAX_RANKING 10

typedef struct {
    char nome[512];
    int ocorrencias;
} Ranking;

typedef struct {
    char caminho[512];
    const char *palavra;
} ThreadArgs;

// Variáveis globais
Ranking ranking[MAX_RANKING];
int ranking_tamanho = 0;
pthread_mutex_t mutex_ranking;

// Função para contar ocorrências de uma palavra em um arquivo
int contar_ocorrencias(const char *arquivo, const char *palavra) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return -1;
    }

    char linha[1024];
    int contagem = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        char *ptr = linha;
        while ((ptr = strstr(ptr, palavra)) != NULL) {
            contagem++;
            ptr += strlen(palavra);
        }
    }

    fclose(fp);
    return contagem;
}

// Atualiza o ranking com mutex
void atualizar_ranking(const char *arquivo, int ocorrencias) {
    pthread_mutex_lock(&mutex_ranking);

    if (ranking_tamanho < MAX_RANKING) {
        strcpy(ranking[ranking_tamanho].nome, arquivo);
        ranking[ranking_tamanho].ocorrencias = ocorrencias;
        ranking_tamanho++;
    } else {
        int min_idx = 0;
        for (int i = 1; i < MAX_RANKING; i++) {
            if (ranking[i].ocorrencias < ranking[min_idx].ocorrencias) {
                min_idx = i;
            }
        }
        if (ocorrencias > ranking[min_idx].ocorrencias) {
            strcpy(ranking[min_idx].nome, arquivo);
            ranking[min_idx].ocorrencias = ocorrencias;
        }
    }

    for (int i = 0; i < ranking_tamanho - 1; i++) {
        for (int j = i + 1; j < ranking_tamanho; j++) {
            if (ranking[j].ocorrencias > ranking[i].ocorrencias) {
                Ranking temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }

    pthread_mutex_unlock(&mutex_ranking);
}

// Função para processar arquivos com threads
void *trabalho_operaria(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int ocorrencias = contar_ocorrencias(args->caminho, args->palavra);
    if (ocorrencias >= 0) {
        atualizar_ranking(args->caminho, ocorrencias);
    }
    return NULL;
}

void processar_diretorio_threads(const char *diretorio, const char *palavra) {
    DIR *dp = opendir(diretorio);
    if (!dp) {
        perror("Erro ao abrir diretório");
        return;
    }

    struct dirent *entry;
    struct stat statbuf;

    pthread_t threads[MAX_THREADS];
    ThreadArgs args[MAX_THREADS];
    int thread_count = 0;

    while ((entry = readdir(dp)) != NULL) {
        char caminho[512];
        snprintf(caminho, sizeof(caminho), "%s/%s", diretorio, entry->d_name);

        if (stat(caminho, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            strcpy(args[thread_count].caminho, caminho);
            args[thread_count].palavra = palavra;

            pthread_create(&threads[thread_count], NULL, trabalho_operaria, &args[thread_count]);
            thread_count++;

            if (thread_count == MAX_THREADS) {
                for (int i = 0; i < thread_count; i++) {
                    pthread_join(threads[i], NULL);
                }
                thread_count = 0;
            }
        }
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    closedir(dp);
}

void imprimir_ranking() {
    printf("\n=== Ranking de Arquivos ===\n");
    pthread_mutex_lock(&mutex_ranking);
    for (int i = 0; i < ranking_tamanho; i++) {
        printf("%d. %s - %d ocorrências\n", i + 1, ranking[i].nome, ranking[i].ocorrencias);
    }
    pthread_mutex_unlock(&mutex_ranking);
}

// Monitoramento contínuo do diretório
void monitorar_diretorio(const char *diretorio, const char *palavra) {
    struct stat estado_anterior[1024];
    int arquivo_count = 0;

    while (1) {
        DIR *dp = opendir(diretorio);
        if (!dp) {
            perror("Erro ao abrir diretório");
            return;
        }

        struct dirent *entry;
        struct stat statbuf;
        int mudou = 0;

        int i = 0;
        while ((entry = readdir(dp)) != NULL) {
            char caminho[512];
            snprintf(caminho, sizeof(caminho), "%s/%s", diretorio, entry->d_name);

            if (stat(caminho, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
                if (i >= arquivo_count || estado_anterior[i].st_mtime != statbuf.st_mtime) {
                    mudou = 1;
                    estado_anterior[i] = statbuf;
                }
                i++;
            }
        }

        arquivo_count = i;
        closedir(dp);

        if (mudou) {
            printf("\nAlteração detectada no diretório. Atualizando...\n");
            ranking_tamanho = 0; // Limpa o ranking
            processar_diretorio_threads(diretorio, palavra);
            imprimir_ranking();
        }

        sleep(5);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: ./paralegrep <palavra>\n");
        return 1;
    }

    const char *palavra = argv[1];

    pthread_mutex_init(&mutex_ranking, NULL);
    monitorar_diretorio("fileset", palavra);
    pthread_mutex_destroy(&mutex_ranking);

    return 0;
}
