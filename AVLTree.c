#include <stdio.h>
#include <stdlib.h>

//untuk mengisi data
struct Node
{
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};
//untuk membuat node baru
struct Node* createNode(int key){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> key = key;
    newNode -> height = 1;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}
//untuk menghitung banyaknya node

int getHeight(struct Node* curr){
    if(curr == NULL){
        return 0;
    }
    return curr -> height;
}

//untuk menghitung banyaknya node
int getMax(int a, int b){
    return a > b ? a : b;
}
//untuk menghitung nilai balance tree nya
int getBalanceFactor(struct Node* curr){
    return getHeight(curr -> left) - getHeight(curr -> right);
}

// right rotate

struct Node* rightRotate(struct Node* curr){
    struct Node* childLeft = curr -> left;
    struct Node* subChildLeft = childLeft -> right;

    childLeft -> right = curr;
    curr -> left = subChildLeft;

    curr -> height  = 1 + getMax(getHeight(curr -> left), getHeight(curr -> right));
    childLeft -> height = 1 + getMax(getHeight(childLeft -> left), getHeight(childLeft -> right));

    return childLeft;
}

//left rotate
struct Node* leftRotate(struct Node* curr){
    struct Node* childRight = curr -> right;
    struct Node* subChildRight = childRight -> left;

    childRight -> left = curr;
    curr -> right = subChildRight;

    curr -> height  = 1 + getMax(getHeight(curr -> left), getHeight(curr -> right));
    childRight -> height = 1 + getMax(getHeight(childRight -> left), getHeight(childRight -> right));

    return childRight;
}

//untuk balancing tree
struct Node* balancing(struct Node* curr){
    curr -> height = 1 + getMax(getHeight(curr -> left), getHeight(curr -> right));
    // left -left
    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr -> left) > 0){
        return rightRotate(curr);
    }
    // right-right
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr -> right)  < 0){
        return leftRotate(curr);
    }
    //left-right
    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr -> left) < 0){
        curr -> left = leftRotate(curr -> left);
        return rightRotate(curr);
    }
    //right-left
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr -> right) > 0){
        curr -> right = rightRotate(curr -> right);
        return leftRotate(curr);
    }
    return curr;
}

//insert tree

struct Node* insert(struct Node* curr, struct Node* newNode){
    if(curr == NULL){
        return newNode;
    }
    if(newNode -> key < curr -> key){
        curr -> left = insert(curr -> left, newNode);
    }else if(newNode -> key > curr -> key){
        curr -> right = insert(curr -> right, newNode);
    }
    return balancing(curr);
}

//delete tree
struct Node *pop(struct Node *curr, int key){
    if(curr == NULL){
        puts("Data Not Found");
        return curr;
    }
    if(key < curr -> key){
        curr -> left = pop(curr -> left, key);
    }else if(key > curr -> key){
        curr -> right = pop(curr -> right, key);
    }

    if(key < curr -> key){
        curr -> left = pop(curr -> left, key);
    }else if(key > curr -> key){
        curr -> right = pop(curr -> right, key);
    }else{
        if(curr -> left == NULL && curr -> right == NULL){
           free(curr);
           curr = NULL;
           return curr;                                                                                                 
    }else if(curr -> left == NULL || curr -> right == NULL){
        struct Node* temp;
        if(curr -> left != NULL)
            temp = curr -> left;
        else
            temp = curr -> right;

        free(curr);
        curr = temp;
    }else{
        struct Node* predeseccor = curr -> left;

        while(predeseccor -> right != NULL){
            predeseccor = predeseccor -> right;
        }
        curr -> key = predeseccor -> key;

        curr -> left = pop(curr -> left, predeseccor -> key);
        }
    }
    return balancing(curr);
}
void menu(){
    puts("1. Insert");
    puts("2. Delete");
    puts("3. Traversal");
    puts("4. Exit");
}
// traversal postorder, preorder, dan inorder
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void postOrder(struct Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
//main function
int main(){
    struct Node *root = NULL;
    int choice, key;

    do{
        menu();
        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Insert: ");
                scanf("%d", &key);
                root = insert(root, createNode(key));
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &key);
                root = pop(root, key);
                break;
            case 3: 
                printf("Preorder: ");
                preorder(root);
                puts(" ");
                printf("Inoder: ");
                inorder(root);
                puts(" ");
                printf("Postorder: ");
                postOrder(root);
                puts(" ");
                break;
            case 4:
                printf("Thank You\n");
                exit(1);
                break;
            default:
                puts("Wrong Choice");
                break;
        }
    }while(choice != 4);
    return 0;
}