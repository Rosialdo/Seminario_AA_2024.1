#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó na árvore AVL
typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

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
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

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
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retornar nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó AVL
int get_balance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Função para inserir uma chave na árvore AVL
AVLNode* insert_avl(AVLNode* node, int key) {
    // Inserção como em uma árvore binária de busca normal
    if (node == NULL)
        return create_node(key);

    if (key < node->key)
        node->left = insert_avl(node->left, key);
    else if (key > node->key)
        node->right = insert_avl(node->right, key);
    else
        return node;  // Chaves duplicadas não são permitidas

    // Atualizar a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter o fator de balanceamento para verificar se este nó se tornou desbalanceado
    int balance = get_balance(node);

    // Caso 1: Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    // Caso 2: Direita-Direita
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    // Caso 3: Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Caso 4: Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    // Retornar o ponteiro (inalterado) do nó
    return node;
}

// Função para liberar a memória da árvore AVL
void free_avl(AVLNode* node) {
    if (node == NULL)
        return;
    free_avl(node->left);
    free_avl(node->right);
    free(node);
}

// Função principal que lê as entradas de um arquivo e insere na árvore AVL
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    AVLNode* root = NULL;

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    int key;
    while (fscanf(file, "%d", &key) != EOF) {
        root = insert_avl(root, key);
    }

    fclose(file);

    free_avl(root);

    return 0;
}
