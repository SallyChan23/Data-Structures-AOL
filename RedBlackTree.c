#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

//membuat node baru
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode -> left = newNode -> right = newNode -> parent = NULL;
    return newNode;
}

//rotasi ke kiri
void rotateLeft(struct Node* node) {
    struct Node* rightChild = node -> right;
    node -> right = rightChild -> left;

    if (node -> right != NULL)
        node -> right -> parent = node;

    rightChild -> parent = node -> parent;

    if (node -> parent == NULL)
        root = rightChild;
    else if (node == node -> parent -> left)
        node -> parent -> left = rightChild;
    else
        node -> parent -> right = rightChild;

    rightChild -> left = node;
    node -> parent = rightChild;
}
//rotasi ke kanan
void rotateRight(struct Node* node) {
    struct Node* leftChild = node -> left;
    node -> left = leftChild -> right;

    if (node -> left != NULL)
        node -> left -> parent = node;

    leftChild -> parent = node -> parent;

    if (node -> parent == NULL)
        root = leftChild;
    else if (node == node -> parent -> left)
        node -> parent -> left = leftChild;
    else
        node -> parent -> right = leftChild;

    leftChild -> right = node;
    node -> parent = leftChild;
}
// fungsi untuk memperbaiki ketika node yang baru dibuat setelah insert
void fixInsert(struct Node* node) {
    while (node != root && node -> parent -> color == RED) {
        struct Node* grandparent = node->parent->parent;
        struct Node* uncle;

        if (node -> parent == grandparent -> left) {
            uncle = grandparent -> right;

            if (uncle != NULL && uncle -> color == RED) {
                grandparent -> color = RED;
                node->parent -> color = BLACK;
                uncle -> color = BLACK;
                node = grandparent;
            } else {
                if (node == node -> parent -> right) {
                    node = node -> parent;
                    rotateLeft(node);
                }

                node->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {
            uncle = grandparent -> left;

            if (uncle != NULL && uncle -> color == RED) {
                grandparent -> color = RED;
                node -> parent -> color = BLACK;
                uncle -> color = BLACK;
                node = grandparent;
            } else {
                if (node == node -> parent -> left) {
                    node = node -> parent;
                    rotateRight(node);
                }

                node -> parent -> color = BLACK;
                grandparent -> color = RED;
                rotateLeft(grandparent);
            }
        }
    }

    root->color = BLACK;
}
//fungsi insert
void insert(int data) {
    struct Node* newNode = createNode(data);
    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (newNode->data < current -> data)
            current = current -> left;
        else
            current = current -> right;
    }

    newNode -> parent = parent;

    if (parent == NULL)
        root = newNode;
    else if (newNode -> data < parent -> data)
        parent -> left = newNode;
    else
        parent -> right = newNode;

    fixInsert(newNode);
}

//fungsi inorder

void inorderTraversal(struct Node* node) {
    if (node == NULL)
        return;

    inorderTraversal(node -> left);
    printf("%d ", node -> data);
    inorderTraversal(node -> right);
}

int main() {
    //contoh insert angka dari soal
    insert(41);
    insert(22);
    insert(5);
    insert(51);
    insert(48);
    insert(29);
    insert(18);
    insert(21);
    insert(45);
    insert(3);

    //untuk mengeluarkan hasil output dalam bentuk inorder
    printf("Inorder traversal: ");
    inorderTraversal(root);
    
    return 0;
}