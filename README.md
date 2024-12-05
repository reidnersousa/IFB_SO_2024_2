README - Paralegrep

Nomes dos Integrantes do Grupo

Nome1 Completo

Nome2 Completo

Nome3 Completo

Como Compilar o Programa

Para compilar o programa, utilize o seguinte comando no terminal:

gcc -o paralegrep paralegrep.c -lpthread

Este comando gera o executável paralegrep.

Como Executar o Programa

Execute o programa no terminal, informando a palavra que deseja buscar:

./paralegrep <palavra>

Exemplo de uso:

./paralegrep sistemas

O programa irá processar os arquivos na pasta fileset, buscar a palavra especificada e exibir o ranking dos 10 arquivos com mais ocorrências.

Descrição do Funcionamento

Busca nos Arquivos:

O programa analisa todos os arquivos do diretório fileset, contando a quantidade de ocorrências da palavra especificada.

Threads:

Utiliza threads operárias para processar os arquivos em paralelo (limite de até 10 threads simultâneas).

Uma thread despachante monitora o diretório fileset a cada 5 segundos e distribui arquivos novos ou modificados para as threads operárias.

Ranking:

Mantém um ranking global dos 10 arquivos com mais ocorrências da palavra buscada.

O ranking é atualizado automaticamente ao detectar alterações no diretório fileset.

Sincronização:

Utiliza mutexes para proteger o acesso à estrutura de ranking e evitar condições de corrida.

Estrutura de Arquivos do Projeto

paralegrep.c: Arquivo principal contendo o código fonte do programa.

fileset/: Diretório contendo os arquivos de texto a serem processados.

Testes e Validação

Antes de entregar, certifique-se de:

Testar o programa com diferentes palavras e conjuntos de arquivos.

Verificar vazamentos de memória usando:

valgrind ./paralegrep <palavra>

Garantir que o ranking exibe corretamente os 10 arquivos com mais ocorrências.

Empacotamento do Projeto

Para entregar o projeto, compacte os arquivos em um único arquivo .zip ou .7z com o seguinte comando:

zip -r T1_SO_nome1nome2nome3.zip paralegrep/

Substitua nome1, nome2 e nome3 pelos primeiros nomes dos integrantes do grupo.

