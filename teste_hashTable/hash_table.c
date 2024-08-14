// O algoritmo é uma tabela hash encadeada com tratamento de colisão por meio
// de listas ligadas. Essa técnica é robusta e eficiente em muitos cenários, especialmente 
// quando a função de hash distribui bem as chaves e o número de colisões é baixo.

// o tratamento de colisão é feito por meio de encadeamento (chaining). A colisão é tratada 
// ao armazenar múltiplos elementos que mapeiam para o mesmo índice da tabela em uma lista ligada

// Quando duas ou mais chaves mapeiam para o mesmo índice na tabela hash (ocorre uma colisão), 
//esses elementos são armazenados em uma lista ligada (linked list).

//Cada posição da tabela hash é, na verdade, um ponteiro para o início de uma lista ligada
// . Se ocorrer uma colisão, o novo elemento é adicionado ao início da lista.

//Dessa forma, múltiplos elementos podem ser armazenados no mesmo índice sem sobrescrever uns aos outros.


#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000

typedef struct Node {
    int key;      // Chave
    int value;    // Valor
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// Função de hash simples
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

//Explicação tratamento de colisão:

//Primeiro, o índice na tabela hash é calculado usando a função hash(key). Esse índice é a posição 
//onde o novo elemento será inserido.

// Um novo nó (newNode) é alocado dinamicamente para armazenar a chave e o valor.

// O próximo nó (next) do novo nó (newNode) é configurado para apontar para o nó que já está armazenado na tabela hash na posição index, se houver um. Isso significa que, se já houver outros elementos com o mesmo índice (ou seja, se houver uma colisão), o novo nó será inserido no início da lista ligada. Isso é feito pela linha: newNode->next = hashTable[index];

//A tabela hash no índice index é então atualizada para apontar para o novo nó (newNode). Isso significa que o novo nó se torna o primeiro nó na lista ligada nesse índice.  sso é feito pela linha: hashTable[index] = newNode;

// exemplo:

// Suponha que você queira inserir dois pares chave-valor: (3, 100) e (1003, 200) e ambos mapeiam para o índice 3 na tabela hash (ou seja, há uma colisão).

// O primeiro par (3, 100) é inserido na posição 3 da tabela hash.

// Quando o segundo par (1003, 200) é inserido, ele também mapeia para a posição 3. Em vez de sobrescrever o valor existente, ele é adicionado no início da lista ligada na posição 3.


// Agora, a posição 3 na tabela hash contém uma lista ligada com dois nós: o primeiro nó contém (1003, 200) e o segundo nó contém (3, 100).



// Inserir chave-valor na tabela hash
void insert(int key, int value) {
    unsigned int index = hash(key);  // Calcula o índice da tabela hash usando a função de hash
    Node* newNode = (Node*)malloc(sizeof(Node));  // Aloca memória para um novo nó
    newNode->key = key;
    newNode->value = value;
    
    // O próximo nó do novo nó será o nó que já está na tabela hash nesse índice (se houver)
    newNode->next = hashTable[index];  
    
    // O novo nó passa a ser o primeiro nó da lista no índice correspondente
    hashTable[index] = newNode;
}


// Imprimir todos os pares chave-valor na tabela hash
void printTable(FILE *outfile) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = hashTable[i];
        while (node != NULL) {
            fprintf(outfile, "Key: %d, Value: %d\n", node->key, node->value);
            node = node->next;
        }
    }
}

void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = hashTable[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");

    if (!infile || !outfile) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    int n;
    fscanf(infile, "%d", &n); // Lê o número de elementos

    int key, value;
    for (int i = 0; i < n; i++) {
        fscanf(infile, "%d %d", &key, &value); // Lê a chave e o valor
        insert(key, value);
    }

    printTable(outfile); // Imprime a tabela hash no arquivo de saída

    // Fechar os arquivos
    fclose(infile);
    fclose(outfile);

    freeTable();  // Libera a memória antes de encerrar o programa

    return 0;
}
