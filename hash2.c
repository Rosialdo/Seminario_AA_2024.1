#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó na árvore AVL
typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Estrutura da tabela hash
typedef struct HashTable {
    AVLNode** table;
    int size;
} HashTable;

// Função para obter a altura de um nó AVL
int height(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para obter o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó AVL
AVLNode* create_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // Novo nó inicialmente é uma folha
    return node;
}

// Função para rotacionar à direita a subárvore com raiz y
AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Executar rotação
    x->right = y;
    y->left = T2;

    // Atualizar alturas
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    // Retornar nova raiz
    return x;
}

// Função para rotacionar à esquerda a subárvore com raiz x
AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Executar rotação
    y->left = x;
    x->right = T2;

    // Atualizar alturas
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // Retornar nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó AVL
int get_balance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Função para inserir uma chave na árvore AVL e balancear a árvore
AVLNode* insert_avl(AVLNode* node, int key) {
    // 1. Inserir como em uma BST normal
    if (node == NULL)
        return create_node(key);

    if (key < node->key)
        node->left = insert_avl(node->left, key);
    else if (key > node->key)
        node->right = insert_avl(node->right, key);
    else
        return node;  // Chaves duplicadas não são permitidas

    // 2. Atualizar a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obter o fator de balanceamento
    int balance = get_balance(node);

    // 4. Balancear a árvore
    // Caso esquerda-esquerda
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    // Caso direita-direita
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    // Caso esquerda-direita
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Caso direita-esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    // Retornar o nó (inalterado) ponteiro
    return node;
}

// Função hash simples (baseada no módulo)
unsigned int hash_function(int key, int table_size) {
    return key % table_size;
}

// Função para criar uma tabela hash
HashTable* create_table(int size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    hash_table->size = size;
    hash_table->table = (AVLNode**)malloc(sizeof(AVLNode*) * size);

    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }

    return hash_table;
}

// Função para inserir uma chave na tabela hash
void insert(HashTable* hash_table, int key) {
    unsigned int index = hash_function(key, hash_table->size);
    hash_table->table[index] = insert_avl(hash_table->table[index], key);
}

// Função para liberar memória de uma árvore AVL
void free_avl(AVLNode* node) {
    if (node == NULL)
        return;
    free_avl(node->left);
    free_avl(node->right);
    free(node);
}

// Função para liberar a memória da tabela hash
void free_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        free_avl(hash_table->table[i]);
    }
    free(hash_table->table);
    free(hash_table);
}

// Função principal para testar a tabela hash com árvores AVL
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int table_size = 10007;  // Tamanho da tabela hash
    HashTable* hash_table = create_table(table_size);

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
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
