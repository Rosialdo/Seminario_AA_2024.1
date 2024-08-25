# Comparação de Desempenho de Tabelas Hash com Tratamento de Colisões usando AVL e Listas Encadeadas

## Descrição:

Este projeto tem como objetivo comparar o desempenho de duas implementações diferentes de Tabelas Hash: uma que usa Árvores AVL para tratamento de colisões e outra que usa Listas Encadeadas. A comparação é feita através da análise do tempo de execução para a inserção de diferentes conjuntos de chaves, com o objetivo de entender as diferenças de eficiência entre as duas abordagens.

## Implementações

### 1. Tabela Hash com Árvore AVL:

- Nesta implementação, colisões na tabela hash são tratadas usando uma Árvore AVL. Cada entrada da tabela hash é uma raiz de uma AVL, que garante que as operações de inserção, remoção e busca sejam realizadas em tempo logarítmico em relação ao número de elementos dentro daquela célula específica da tabela.

### 2. Tabela Hash com Lista Encadeada:

- Nesta implementação, colisões na tabela hash são tratadas utilizando listas encadeadas simples. Cada entrada da tabela hash contém uma lista encadeada onde novas chaves são adicionadas no início da lista.

## Estrutura dos Arquivos

- `hashAVL.c`: Implementa a Tabela Hash com Listas Encadeadas.

- `hashEncadeado.c`: Implementa a Tabela Hash com Listas Encadeadas.

- `monitoramento.py`: Script Python que executa ambos os programas com diferentes arquivos de entrada, mede o tempo de execução e gera gráficos comparativos.

## Dependências

- Python 3.x
- `matplotlib` para geração de gráficos.
- `statistics` para cálculo de métricas de desempenho.


## Como executar:

### 1. Compilar os programas em C:

Execute os comandos abaixo para compilar ambos os programas:

```bash
gcc hashAVL.c -o avl
gcc hashEncadeado.c -o encadeado
````

### 2. Preparar arquivos de entrada:

- Coloque os arquivos de entrada na pasta input_files. Cada arquivo deve conter uma lista de números inteiros (um por linha).

### 3. Executar o monitoramento:

- O script `monitoramento.py` executa os programas avl e encadeado com os diferentes arquivos de entrada e mede o tempo de execução. Execute o script com o comando:

```python3
python3 monitoramento.py
```

- O script realizará um número configurável de execuções de aquecimento e medição, e então calculará e exibirá o tempo médio e mediano de execução para cada abordagem.

### Visualizar os Resultados:

- O script `monitoramento.py` gerará gráficos comparando o tempo de execução das duas abordagens em função do número de entradas em cada arquivo de teste.

- o script gera gráficos comparativos que ajudam a visualizar e entender o desempenho das duas implementações de Tabelas Hash: uma usando Árvores AVL e outra usando Listas Encadeadas para tratamento de colisões. Aqui está uma explicação detalhada sobre os gráficos gerados:

## 1. Gráfico de Tempo Médio de Execução (average):

- Este gráfico mostra a comparação do tempo médio de execução das duas abordagens (Árvore AVL e Lista Encadeada) em função do número de entradas nos arquivos de teste.

- Eixo X (Número de Entradas):
O eixo X representa o número de entradas em cada arquivo de teste. Cada ponto no gráfico corresponde a um arquivo de entrada específico, e o valor de X indica quantas chaves (ou números) foram inseridas na tabela hash.

- Eixo Y (Tempo de Execução Médio):
O eixo Y representa o tempo médio de execução em segundos para inserir todas as chaves de um arquivo de entrada na tabela hash. Este tempo é calculado a partir de várias execuções repetidas, descartando outliers para garantir uma medição precisa.

- Linhas:
Cada linha no gráfico representa uma abordagem diferente:

- Linha da Árvore AVL: Mostra como o tempo médio de inserção varia conforme o número de entradas aumenta, usando Árvores AVL para tratar colisões.
- Linha da Lista Encadeada: Mostra o tempo médio de inserção usando Listas Encadeadas.

- Interpretação:

Se a linha da Árvore AVL se mantiver abaixo da linha da Lista Encadeada, isso indica que a abordagem AVL foi, em média, mais rápida para os arquivos de entrada testados.
A inclinação de cada linha indica a escalabilidade da abordagem. Uma linha com inclinação mais suave sugere que a abordagem lida melhor com o aumento do número de entradas.

## 2. Gráfico de Tempo Mediano de Execução (median)

Este gráfico é semelhante ao gráfico de tempo médio de execução, mas foca na mediana do tempo de execução.

- Eixo X (Número de Entradas):
Assim como no gráfico anterior, o eixo X mostra o número de entradas nos arquivos de teste.

- Eixo Y (Tempo de Execução Mediano):
O eixo Y mostra o tempo mediano de execução em segundos para cada abordagem. A mediana é uma métrica robusta que é menos afetada por outliers extremos, proporcionando uma visão mais estável do desempenho típico.

- Linhas:

- Linha da Árvore AVL: Representa o tempo mediano de inserção usando a abordagem AVL.
- Linha da Lista Encadeada: Representa o tempo mediano de inserção usando a abordagem de Lista Encadeada.

- Interpretação:

Comparando as duas linhas, podemos ver qual abordagem consistentemente apresenta um desempenho mais estável (com menos variações inesperadas).
Uma menor variação na linha da Árvore AVL ou Lista Encadeada sugere que a abordagem é mais previsível e menos propensa a picos de tempo de execução, mesmo com variações no número de entradas.



# Autores: Venícius Jacob, Rosialdo Vidinho
