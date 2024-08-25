#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da Árvore AVL
typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// Estrutura da Tabela Hash
typedef struct HashTable {
    AVLNode** table;
    int size;
} HashTable;

// Função para obter a altura de um nó da AVL
int height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função para calcular o valor máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó da Árvore AVL
AVLNode* create_avl_node(int key) {
    AVLNode* new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->height = 1;  // Novo nó inicialmente é uma folha
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Função para realizar uma rotação à direita na AVL
AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Realizar rotação
    x->right = y;
    y->left = T2;

    // Atualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retornar nova raiz
    return x;
}

// Função para realizar uma rotação à esquerda na AVL
AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Realizar rotação
    y->left = x;
    x->right = T2;

    // Atualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retornar nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó da AVL
int get_balance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Função para inserir um nó na Árvore AVL
AVLNode* insert_avl(AVLNode* node, int key) {
    if (node == NULL) {
        return create_avl_node(key);
    }

    if (key < node->key) {
        node->left = insert_avl(node->left, key);
    } else if (key > node->key) {
        node->right = insert_avl(node->right, key);
    } else {
        // Chave duplicada, não permitida
        return node;
    }

    // Atualizar a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter o fator de balanceamento deste ancestral nó
    int balance = get_balance(node);

    // Casos de rotação para balanceamento
    if (balance > 1 && key < node->left->key) {
        return right_rotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return left_rotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

// Função hash simples (baseada no módulo)
unsigned int hash_function(int key, int table_size) {
    return key % table_size;
}

// Função para criar a Tabela Hash
HashTable* create_table(int size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    if (hash_table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    hash_table->size = size;
    hash_table->table = (AVLNode**)malloc(sizeof(AVLNode*) * size);
    if (hash_table->table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

// Função para inserir uma chave na Tabela Hash usando Árvore AVL para tratamento de colisões
void insert(HashTable* hash_table, int key) {
    unsigned int index = hash_function(key, hash_table->size);
    hash_table->table[index] = insert_avl(hash_table->table[index], key);
}

// Função para liberar a memória da Árvore AVL
void free_avl(AVLNode* node) {
    if (node != NULL) {
        free_avl(node->left);
        free_avl(node->right);
        free(node);
    }
}

// Função para liberar a memória da Tabela Hash
void free_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        free_avl(hash_table->table[i]);
    }
    free(hash_table->table);
    free(hash_table);
}

// Função principal para testar a Tabela Hash com AVL
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int table_size = 10007;  // Tamanho da Tabela Hash
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