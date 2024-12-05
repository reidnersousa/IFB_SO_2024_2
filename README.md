# Resumo do Projeto e Etapas

O projeto tem como objetivo criar um sistema multithread chamado Paralegrep, que busca palavras em arquivos dentro de um diretório, exibe o ranking dos 10 arquivos com mais ocorrências e monitora continuamente o diretório para atualizações.

## Estrutura Inicial do Projeto

### O que foi feito:

- Criada a pasta do projeto paralegrep com a subpasta fileset para armazenar os arquivos de texto.
- Implementado o programa base em C (`paralegrep.c`).
- Testado com um único arquivo para verificar a contagem de palavras.
- Implementado código para listar e processar todos os arquivos da pasta `fileset`.
- Adicionada a funcionalidade para contar palavras em múltiplos arquivos, com suporte a qualquer número de arquivos.
- Adicionadas threads operárias para processar os arquivos em paralelo (limite de até 10 threads simultâneas).
- Cada thread é responsável por contar as ocorrências da palavra em um arquivo específico.

### Estrutura de Ranking dos Arquivos 
- Implementada a estrutura de ranking global para armazenar os 10 arquivos com mais ocorrência.
- Proteção do ranking com mutexes para evitar condições de corrida
- Ordenação do ranking em ordem decrescente.
- Impressão do ranking após o processamento dos arquivos.

### Monitoramento do Diretório
- Adicionado monitoramento contínuo do diretório `fileset` a cada 5 segundos.
- Implementada verificação de alteração (novos arquivos ou modificações) usando `stat`.
- Atualização automática do ranking ao detectar alterações.

## Integrantes do Grupo
- Cesar
- Emerson
- Reidner

### Como Compilar o programa

Para compilar o programa, utilize o seguinte comando no terminal: 
````
gcc -o paralegrep paralegrep.c -lpthread

````
Este comando gera o executável `paralegrep`

### Como Executar o Programa

Executa o programa no terminal, informando a palavra que deseja buscar: 
````
./paralegrap <palavra>
````
Exemplo de uso: 
````
./paralegrep sistemas
````
O programa irá processar os arquivos na pasta `fileset`, buscar a palavra especificada e exibir o ranking dos 10 arquivos com mais ocorrências

## Descrição do Funcionamento

### 1.Busca nos Arquivos

O programa analisa todos os arquivos do diretório `fileset`, contando a quantidade de ocorrências da palavra especificada.

### 2.Threads

- Utiliza threads operárias para processar os arquivos em paralelo (limite de até 10 threads simultâneas).
- Uma thread despachante monitora o diretório `fileset` a cada 5 segundos e distribui arquivos novos ou modificados para as threads operárias.

### 3.Ranking

- Mantém um ranking global dos 10 arquivos com mais ocorrências da palavra buscada.
- O ranking é atualizado automaticamente ao detectar alterações no diretório `fileset`.

### 4.Sincronização

- Utiliza mutexes para proteger o acesso à estrutura de ranking e evitar condições de corrida.

#Estrutura de Arquivos do Projeto
- `paralegrep.c`: Arquivo principal contendo o código fonte do programa.
- `fileset/`: Diretório contendo os arquivos de texto a serem processados.

# Teste e Validação

Antes de entregar, certifique-se de: 
- 1. Teste o programa com diferente palavra e conjuntos de arquivos
- 2. Verificar vazamentos de memória usando:
```
valgrind ./paralegrep <palavra>
```
- 3. Garantir que o ranking exibe corretamente os 10 arquivos com mais ocorrência.

## Empacotamento do Projeto

Para entregar o projeto, compacte os arquivos em um único arquivo `.zip` ou `7z` com o seguinte comando

````
zip -r T1_SO_CesaerEmersonReidner.zip paralegrep/
````

