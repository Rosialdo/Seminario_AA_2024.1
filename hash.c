#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10007 // Tamanho da tabela hash, de preferência um número primo

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** table;
} HashTable;

unsigned int hash_function(char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    return value % TABLE_SIZE;
}

HashTable* create_table() {
    HashTable* hash_table = malloc(sizeof(HashTable));
    hash_table->table = malloc(sizeof(Node*) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }

    return hash_table;
}

void insert(HashTable* hash_table, char* key) {
    unsigned int index = hash_function(key);
    Node* new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

void free_table(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = hash_table->table[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    HashTable* hash_table = create_table();

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;
        insert(hash_table, line);
    }

    fclose(file);
    free_table(hash_table);

    return 0;
}
