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

// Inserir chave-valor na tabela hash
void insert(int key, int value) {
    unsigned int index = hash(key);  // Calcula o índice da tabela hash usando a função de hash
    Node* newNode = (Node*)malloc(sizeof(Node));  // Aloca memória para um novo nó
    if (!newNode) {  // Verificar se a alocação foi bem-sucedida
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    
    // O próximo nó do novo nó será o nó que já está na tabela hash nesse índice (se houver)
    newNode->next = hashTable[index];  
    
    // O novo nó passa a ser o primeiro nó da lista no índice correspondente
    hashTable[index] = newNode;
}

// Liberar a memória alocada para a tabela hash
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
    if (argc != 2) {  // Espera apenas um argumento (arquivo de entrada)
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    if (!infile) {
        return 1;
    }

    int n;
    fscanf(infile, "%d", &n); // Lê o número de elementos

    int key, value;
    for (int i = 0; i < n; i++) {
        fscanf(infile, "%d %d", &key, &value); // Lê a chave e o valor
        insert(key, value);
    }

    // Fechar o arquivo de entrada
    fclose(infile);

    freeTable();  // Libera a memória antes de encerrar o programa

    return 0;
}
