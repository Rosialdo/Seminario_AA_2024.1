#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista encadeada
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Estrutura da tabela hash
typedef struct HashTable {
    Node** table;
    int size;
} HashTable;

// Função hash simples (baseada no módulo)
unsigned int hash_function(int key, int table_size) {
    return key % table_size;
}

// Função para criar um novo nó da lista encadeada
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

// Função para criar a tabela hash
HashTable* create_table(int size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    if (hash_table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    hash_table->size = size;
    hash_table->table = (Node**)malloc(sizeof(Node*) * size);
    if (hash_table->table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

// Função para inserir uma chave na tabela hash usando lista encadeada
void insert(HashTable* hash_table, int key) {
    unsigned int index = hash_function(key, hash_table->size);
    Node* new_node = create_node(key);
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

// Função para liberar a memória da tabela hash
void free_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}

// Função principal para testar a tabela hash
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int table_size = 10007;  // Tamanho da tabela hash
    HashTable* hash_table = create_table(table_size);

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        free_table(hash_table);
        return 1;
    }

    int key;
    while (fscanf(file, "%d", &key) != EOF) {
        insert(hash_table, key);
    }

    fclose(file);
    free_table(hash_table);
    return 0;
}
