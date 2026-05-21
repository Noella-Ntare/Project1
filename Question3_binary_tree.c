#include <stdio.h>
#include <stdlib.h>

struct Node {

    int data;

    struct Node *left;
    struct Node *right;
};

// create a new node
struct Node* createNode(int value) {

    struct Node *newNode;

    newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->data = value;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert node 
struct Node* insert(struct Node *root, int value) {


    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Print leaf nodes
void printLeafNodes(struct Node *root) {

    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }

    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Find parent
struct Node* findParent(struct Node *root, int value) {

    if (root == NULL) {
        return NULL;
    }

    if ((root->left != NULL && root->left->data == value) ||
        (root->right != NULL && root->right->data == value)) {

        return root;
    }

    if (value < root->data) {
        return findParent(root->left, value);
    }

    return findParent(root->right, value);
}

// Find node
struct Node* findNode(struct Node *root, int value) {

    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return findNode(root->left, value);
    }

    return findNode(root->right, value);
}

// Print siblings
void printSiblings(struct Node *root, int value) {

    struct Node *parent = findParent(root, value);

    if (parent == NULL) {
        printf("No siblings found.\n");
        return;
    }

    if (parent->left != NULL && parent->left->data != value) {
        printf("%d\n", parent->left->data);
    }

    if (parent->right != NULL && parent->right->data != value) {
        printf("%d\n", parent->right->data);
    }
}

// Print grandchildren
void printGrandchildren(struct Node *node) {

    if (node == NULL) {
        return;
    }

    int found = 0;

    
    if (node->left != NULL) {

        if (node->left->left != NULL) {
            printf("%d\n", node->left->left->data);
            found = 1;
        }

        if (node->left->right != NULL) {
            printf("%d\n", node->left->right->data);
            found = 1;
        }
    }

    // Right child's children
    if (node->right != NULL) {

        if (node->right->left != NULL) {
            printf("%d\n", node->right->left->data);
            found = 1;
        }

        if (node->right->right != NULL) {
            printf("%d\n", node->right->right->data);
            found = 1;
        }
    }

    if (!found) {
        printf("No grandchildren found.\n");
    }
}

// Free memory
void freeTree(struct Node *root) {

    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main() {

    // Array of integers
    int values[] = {
        10, 25, 30, 15, 50, 60, 70, 35, 45, 55,
        65, 75, 80, 90, 100, 110, 20, 40, 85, 95
    };

    int size = 20;

    struct Node *root = NULL;

    // Build tree
    for (int i = 0; i < size; i++) {
        root = insert(root, values[i]);
    }

    printf("Root Node: %d\n", root->data);

    printf("\nLeaf Nodes:\n");
    printLeafNodes(root);

    // User selects a node
    int value;

    printf("\n\nEnter node value: ");
    scanf("%d", &value);

    struct Node *selectedNode = findNode(root, value);

    // for invalid input
    if (selectedNode == NULL) {

        printf("Node not found in the tree.\n");

        freeTree(root);

        return 0;
    }

    // Print parent
    struct Node *parent = findParent(root, value);

    printf("\nParent:\n");

    if (parent != NULL) {
        printf("%d\n", parent->data);
    }
    else {
        printf("This node is the root node.\n");
    }

    // Print siblings
    printf("\nSiblings:\n");
    printSiblings(root, value);

    // Print grandchildren
    printf("\nGrandchildren:\n");
    printGrandchildren(selectedNode);

    // Free memory
    freeTree(root);

    return 0;
}