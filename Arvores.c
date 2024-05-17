#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height; // altura do nó
};

// Função auxiliar para calcular a altura de um nó
int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função auxiliar para calcular o fator de balanceamento de um nó
int getBalanceFactor(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Função auxiliar para atualizar a altura de um nó
void updateHeight(struct Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função auxiliar para criar um novo nó na árvore
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // inicialmente, a altura é 1
    return newNode;
}

// Função auxiliar para realizar uma rotação simples à esquerda
struct Node* rotateLeft(struct Node* node) {
    struct Node* newRoot = node->right;
    struct Node* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

// Função auxiliar para realizar uma rotação simples à direita
struct Node* rotateRight(struct Node* node) {
    struct Node* newRoot = node->left;
    struct Node* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

// Função de inserção de um nó na árvore AVL
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        // o nó já existe, não é permitida duplicação de valores
        return root;
    }

    updateHeight(root);

    int balanceFactor = getBalanceFactor(root);

    // Realiza as rotações necessárias para balancear a árvore
    if (balanceFactor > 1) {
        if (data < root->left->data) {
            // Caso de rotação LL
            return rotateRight(root);
        } else {
            // Caso de rotação LR
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if (balanceFactor < -1) {
        if (data > root->right->data) {
            // Caso de rotação RR
            return rotateLeft(root);
        } else {
            // Caso de rotação RL
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

// Função de caminhamento pré-ordem
void preorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    printf("%d ", root->data);  // Visita o nó atual (raiz)
    preorderTraversal(root->left);  // Percorre a subárvore esquerda em pré-ordem
    preorderTraversal(root->right);  // Percorre a subárvore direita em pré-ordem
}

// Função de busca em árvore binária
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    
    if (key < root->data) {
        return search(root->left, key);  // Busca na subárvore esquerda
    } else {
        return search(root->right, key);  // Busca na subárvore direita
    }
}

// Função principal
int main() {
    // Construção da árvore binária
    struct Node* binaryRoot = NULL;
    binaryRoot = insert(binaryRoot, 1);
    binaryRoot = insert(binaryRoot, 2);
    binaryRoot = insert(binaryRoot, 3);
    binaryRoot = insert(binaryRoot, 4);
    binaryRoot = insert(binaryRoot, 5);
    
    // Executa os caminhamentos na árvore binária
    printf("Árvore binária:\n");
    printf("Caminhamento pré-ordem: ");
    preorderTraversal(binaryRoot);
    printf("\n");
    
    // Testa a função de busca na árvore binária
    int binaryKey = 5;
    struct Node* binaryResult = search(binaryRoot, binaryKey);
    if (binaryResult != NULL) {
        printf("%d encontrado na árvore binária.\n", binaryKey);
    } else {
        printf("%d não encontrado na árvore binária.\n", binaryKey);
    }
    
    // Construção da árvore AVL
    struct Node* avlRoot = NULL;
    avlRoot = insert(avlRoot, 4);
    avlRoot = insert(avlRoot, 2);
    avlRoot = insert(avlRoot, 6);
    avlRoot = insert(avlRoot, 1);
    avlRoot = insert(avlRoot, 3);
    avlRoot = insert(avlRoot, 5);
    avlRoot = insert(avlRoot, 7);
    
    // Executa os caminhamentos na árvore AVL
    printf("\nÁrvore AVL:\n");
    printf("Caminhamento pré-ordem: ");
    preorderTraversal(avlRoot);
    printf("\n");
    
    // Testa a função de busca na árvore AVL
    int avlKey = 5;
    struct Node* avlResult = search(avlRoot, avlKey);
    if (avlResult != NULL) {
        printf("%d encontrado na árvore AVL.\n", avlKey);
    } else {
        printf("%d não encontrado na árvore AVL.\n", avlKey);
    }
    
    return 0;
}