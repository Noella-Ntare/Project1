#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for BST node
struct Node {

    char firstName[50];
    char lastName[50];
    int grade;

    struct Node *left;
    struct Node *right;
};

// Create new node
struct Node* createNode(char firstName[], char lastName[], int grade) {

    struct Node *newNode;

    newNode = (struct Node*) malloc(sizeof(struct Node));

    strcpy(newNode->firstName, firstName);
    strcpy(newNode->lastName, lastName);

    newNode->grade = grade;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert into BST using last name as key
struct Node* insert(struct Node *root,
                    char firstName[],
                    char lastName[],
                    int grade) {

    // Create node if tree is empty
    if (root == NULL) {

        return createNode(firstName, lastName, grade);
    }

    // Compare last names
    if (strcmp(lastName, root->lastName) < 0) {

        root->left = insert(root->left,
                            firstName,
                            lastName,
                            grade);
    }

    // Duplicate last names go to the right
    else {

        root->right = insert(root->right,
                             firstName,
                             lastName,
                             grade);
    }

    return root;
}

// Search student by last name
void search(struct Node *root, char lastName[]) {

    if (root == NULL) {

        printf("Student not found.\n");
        return;
    }

    int compare = strcmp(lastName, root->lastName);

    // Search left
    if (compare < 0) {

        search(root->left, lastName);
    }

    // Search right
    else if (compare > 0) {

        search(root->right, lastName);
    }

    // Found
    else {

        printf("\nStudent Record Found:\n");

        printf("First Name: %s\n", root->firstName);
        printf("Last Name : %s\n", root->lastName);
        printf("Grade     : %d\n", root->grade);

        // Continue searching right for duplicates
        search(root->right, lastName);
    }
}

// Display records in sorted order
void inOrder(struct Node *root) {

    if (root == NULL) {
        return;
    }

    inOrder(root->left);

    printf("%s %s %d\n",
           root->firstName,
           root->lastName,
           root->grade);

    inOrder(root->right);
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

    FILE *file;

    file = fopen("students.txt", "r");

    // Handle missing file
    if (file == NULL) {

        printf("Error opening file.\n");
        return 1;
    }

    struct Node *root = NULL;

    char firstName[50];
    char lastName[50];
    int grade;

    int records = 0;

    // Read records from file
    while (fscanf(file, "%[^|]| %[^|]| %d\n",
                  firstName,
                  lastName,
                  &grade) == 3) {

        root = insert(root,
                      firstName,
                      lastName,
                      grade);

        records++;
    }

    fclose(file);

    // Handle empty file
    if (records == 0) {

        printf("No valid records found.\n");
        return 1;
    }

    // Display all records
    printf("Student Records Sorted by Last Name:\n\n");

    inOrder(root);

    // Search operation
    char searchName[50];

    printf("\nEnter last name to search: ");
    scanf("%s", searchName);

    search(root, searchName);

    // Free memory
    freeTree(root);

    return 0;
}