# Comparação de Desempenho de Tabelas Hash com Tratamento de Colisões usando AVL e Listas Encadeadas

## Descrição:

Este projeto tem como objetivo comparar o desempenho de duas implementações diferentes de Tabelas Hash: uma que usa Árvores AVL para tratamento de colisões e outra que usa Listas Encadeadas. A comparação é feita através da análise do tempo de execução para a inserção de diferentes conjuntos de chaves, com o objetivo de entender as diferenças de eficiência entre as duas abordagens.

## Implementações

### 1. Tabela Hash com Árvore AVL:

- Nesta implementação, colisões na tabela hash são tratadas usando uma Árvore AVL. Cada entrada da tabela hash é uma raiz de uma AVL, que garante que as operações de inserção, remoção e busca sejam realizadas em tempo logarítmico em relação ao número de elementos dentro daquela célula específica da tabela.

### 2. Tabela Hash com Lista Encadeada:

## Estrutura dos Arquivos

- `hashAVL.c`: Implementa a Tabela Hash com Listas Encadeadas.

- `hashEncadeado.c`: Implementa a Tabela Hash com Listas Encadeadas.

- `monitoramento.py`: Script Python que executa ambos os programas com diferentes arquivos de entrada, mede o tempo de execução e gera gráficos comparativos.

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

# Autores: Venícius Jacob, Rosialdo Vidinho