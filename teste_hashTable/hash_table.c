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
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    
    // O próximo nó do novo nó será o nó que já está na tabela hash nesse índice (se houver)
    newNode->next = hashTable[index];  
    
    // O novo nó passa a ser o primeiro nó da lista no índice correspondente
    hashTable[index] = newNode;
}

// Imprimir todos os pares chave-valor na tabela hash de forma encadeada
void printTable(FILE *outfile) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = hashTable[i];
        while (node != NULL) {
            fprintf(outfile, "Key: %d, Value: %d", node->key, node->value);
            Node* nextNode = node->next;
            // Percorre os nós seguintes que têm a mesma chave (colisão)
            while (nextNode != NULL && nextNode->key == node->key) {
                fprintf(outfile, " - %d", nextNode->value);
                nextNode = nextNode->next;
            }
            fprintf(outfile, "\n");
            node = nextNode;  // Avança para o próximo nó diferente
        }
    }
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

    // printTable(outfile); // Imprime a tabela hash no arquivo de saída

    // Fechar os arquivos
    fclose(infile);
    fclose(outfile);

    freeTable();  // Libera a memória antes de encerrar o programa

    return 0;
}
