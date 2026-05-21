#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student information
struct Student {
    char firstName[50];
    char lastName[50];
    char studentID[20];
    int grade;
};

// Function to swap two students
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Student students[], int low, int high) {

    struct Student pivot = students[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        // Sort by grade
        if (students[j].grade < pivot.grade) {
            i++;
            swap(&students[i], &students[j]);
        }

        // If grades are equal, sort by first name
        else if (students[j].grade == pivot.grade &&
                 strcmp(students[j].firstName, pivot.firstName) < 0) {

            i++;
            swap(&students[i], &students[j]);
        }
    }

    swap(&students[i + 1], &students[high]);

    return i + 1;
}

// Quick Sort
void quickSort(struct Student students[], int low, int high) {

    if (low < high) {

        int pivotIndex = partition(students, low, high);

        quickSort(students, low, pivotIndex - 1);
        quickSort(students, pivotIndex + 1, high);
    }
}

int main() {

    FILE *inputFile;
    FILE *outputFile;

    struct Student students[100];

    int count = 0;

    // Open input file
    inputFile = fopen("students.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read student records from file
    while (fscanf(inputFile, "%s %s %s %d",
                  students[count].firstName,
                  students[count].lastName,
                  students[count].studentID,
                  &students[count].grade) == 4) {

        count++;
    }

    fclose(inputFile);

    // Quick Sort students
    quickSort(students, 0, count - 1);

    // Open output file
    outputFile = fopen("sorted_students.txt", "w");

    if (outputFile == NULL) {
        printf("Error creating output file.\n");
        return 1;
    }

    // Write sorted records to the output file
    for (int i = 0; i < count; i++) {

        fprintf(outputFile, "%s %s %s %d\n",
                students[i].firstName,
                students[i].lastName,
                students[i].studentID,
                students[i].grade);
    }

    fclose(outputFile);

    // Display sorted students
    printf("Sorted Student Records:\n\n");

    for (int i = 0; i < count; i++) {

        printf("%s %s %s %d\n",
               students[i].firstName,
               students[i].lastName,
               students[i].studentID,
               students[i].grade);
    }

    return 0;
}