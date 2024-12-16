# Paralegrep
O Paralegrep é um sistema multithread para busca de palavras em arquivos dentro de um diretório, que exibe o ranking dos 10 arquivos com mais ocorrências da palavra buscada. O sistema monitora continuamente o diretório para atualizações, detectando novos arquivos ou modificações nos existentes.

## Integrantes do Grupo
- Cesar
- Emerson
- Reidner

## Como Compilar o programa
Para compilar o programa, utilize o seguinte comando no terminal:
```
gcc -o paralegrep paralegrep.c -lpthread
```
Este comando gera o executável paralegrep

## Como Executar o Programa
Executa o programa no terminal, informando a palavra que deseja buscar:
``` 
./paralegrap <palavra>
```
Exemplo de uso:
```
./paralegrep sistemas
```
O programa irá processar os arquivos na pasta `fileset`, buscar a palavra especificada e exibir o ranking dos 10 arquivos com mais ocorrências



## Descrição do Funcionamento
### 1.Busca nos Arquivos
O programa analisa todos os arquivos do diretório `fileset`, contando a quantidade de ocorrências da palavra especificada.

### 2.Threads
Utiliza threads operárias para processar os arquivos em paralelo (limite de até 10 threads simultâneas).
Uma thread despachante monitora o diretório fileset a cada 5 segundos e distribui arquivos novos ou modificados para as threads operárias.
### 3.Ranking
Mantém um ranking global dos 10 arquivos com mais ocorrências da palavra buscada.
O ranking é atualizado automaticamente ao detectar alterações no diretório `fileset`.
### 4.Sincronização
Utiliza mutexes para proteger o acesso à estrutura de ranking e evitar condições de corrida.




## Estrutura Projeto
### Diretórios e Arquivos:
- `paralegrep.c`: Arquivo principal contendo o código fonte do programa.
- `fileset/`: Diretório contendo os arquivos de texto a serem processados.


## Componentes do Código 
### 1.Função `conta_ocorrencias`
- Descrição : Realiza a busca de uma palavra em um arquivo e retorna o número de ocorrências.
- Detalhes Técnicos: Utiliza `fgets` para ler o arquivo linha a linha e `strstr` para localizar a palavra.

### 2. Função `atualizar_ranking`
- Descrição: Atualiza o ranking global protegendo o acesso com `mutex` para evitar condições de corrida
- Funcionamento:
-- Caso o ranking tenha menos de 10 arquivos, adiciona diretamente
-- Se o ranking já possui 10 itens, substitui o arquivo com menos ocorrências, se necessário.
-- Ordena o ranking em ordem decrescente.
-- Usa um mutex para garantir que a atualização seja feita de forma segura em ambientes de múltiplas threads.
### 3 Threads Operárias `trabalho_operaria`
- Descrição: Cada thread processa um arquivo individualmente, contando as ocorrências da palavra
- Funcionamento:
-- `contar_ocorrencias` para conta as ocorrências da palavra e, sem seguida , chama `atualizar_ranking` para atualizar o ranking.
  
### 4 Função `processar_diretorio_threads`
- Descrição: Lê os arquivos de um diretório e cria threads para processar até 10 arquivos simultaneamente.
- Sincroniza as threads (com `pthread_join`) após atingir o limite de 10 threads antes de criar novas.

### 5 Função `imprimir_ranking`
- Descrição: Imprime o ranking atualizado dos arquivos com maior número de ocorrências da palavra.

###  6 Função `monitorar_diretorio`
- Descrição : Monitora o diretório `fileset` continuamente, verificando alterações a cada 5 segundos.
- Utiliza a função `stat` para obter informações sobre os arquivos no diretório. 
- Reprocessa os arquivos alterados ou novos e atualiza o ranking.
## Empacotamento do Projeto
Para entregar o projeto, compacte os arquivos em um único arquivo .zip ou 7z com o seguinte comando
```
zip -r T1_SO_CesaerEmersonReidner.zip paralegrep/
```

## Funcionamento do Sistema
### 1 Inicialização:
- Ao ser Ao ser executado, o programa processa os arquivos presentes na pasta `fileset`.
### 2 Execução Multithread:
- Cada thread operária analisa um arquivo, contando ocorrências da palavra especificada.
### 3 Atualização do Ranking:
- O ranking é continuamente atualizado e exibido após cada processamento.
### 4 Monitoramento Contínuo:
- A cada 5 segundos, a thread despachante verifica o diretório em busca de alterações e reprocessa os arquivos quando necessário.

## Conclusão
O Paralegrep foi desenvolvido para demonstrar:

- Uso eficiente de threads para processamento paralelo.
- Sincronização de recursos compartilhados com mutexes.
- Monitoramento dinâmico de diretórios para detectar alterações em tempo real
