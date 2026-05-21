#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Structure for a bus stop
struct BusStop {
    char name[50];
    int number;

    struct BusStop *next;
    struct BusStop *prev;
};

// Function to create a new bus stop
struct BusStop* createStop(char name[], int number) {

    struct BusStop *newStop;

    newStop = (struct BusStop*) malloc(sizeof(struct BusStop));

    strcpy(newStop->name, name);
    newStop->number = number;

    newStop->next = NULL;
    newStop->prev = NULL;

    return newStop;
}

// Add stop at the end
void addStop(struct BusStop **head, struct BusStop **tail,
             char name[], int number) {

    struct BusStop *newStop = createStop(name, number);

    // If list is empty
    if (*head == NULL) {
        *head = newStop;
        *tail = newStop;
    }

    else {
        (*tail)->next = newStop;
        newStop->prev = *tail;
        *tail = newStop;
    }
}

// Move forward
void moveForward(struct BusStop *head) {

    struct BusStop *temp = head;

    printf("\nMoving from Home to Campus:\n");

    while (temp != NULL) {

        printf("Stop %d : %s\n", temp->number, temp->name);

        // 3 second delay
        #ifdef _WIN32
            Sleep(3000);
        #else
            sleep(3);
        #endif

        temp = temp->next;
    }

    printf("Reached Campus.\n");
}

// Move backward
void moveBackward(struct BusStop *tail) {

    struct BusStop *temp = tail;

    printf("\nMoving from Campus to Home:\n");

    while (temp != NULL) {

        printf("Stop %d : %s\n", temp->number, temp->name);

        // 3 second delay
        #ifdef _WIN32
            Sleep(3000);
        #else
            sleep(3);
        #endif

        temp = temp->prev;
    }

    printf("Reached Home.\n");
}

// Free memory
void freeList(struct BusStop *head) {

    struct BusStop *temp;

    while (head != NULL) {

        temp = head;
        head = head->next;

        free(temp);
    }
}

int main() {

    struct BusStop *head = NULL;
    struct BusStop *tail = NULL;

    int n;

    printf("Enter number of bus stops: ");
    scanf("%d", &n);

    // Read initial bus stops
    for (int i = 0; i < n; i++) {

        char name[50];
        int number;

        printf("\nEnter bus stop name: ");
        scanf("%s", name);

        printf("Enter stop number: ");
        scanf("%d", &number);

        addStop(&head, &tail, name, number);
    }

    int choice;

    do {

        printf("\n===== MENU =====\n");
        printf("1. Move Forward\n");
        printf("2. Move Backward\n");
        printf("3. Add New Stop\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            moveForward(head);
        }

        else if (choice == 2) {
            moveBackward(tail);
        }

        else if (choice == 3) {

            char name[50];
            int number;

            printf("Enter new stop name: ");
            scanf("%s", name);

            printf("Enter new stop number: ");
            scanf("%d", &number);

            addStop(&head, &tail, name, number);

            printf("New stop added successfully.\n");
        }

    } while (choice != 4);

    // Free memory before ending program
    freeList(head);

    printf("Program ended successfully.\n");

    return 0;
}