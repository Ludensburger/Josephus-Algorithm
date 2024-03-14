
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the circular linked list

// Define the structure for a node in the circular linked list
struct Node {
    int data;
    struct Node *next;
};

int size = 0;

struct Node *newNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertEnd(struct Node **head, int data, int n) {
    struct Node *new_node = newNode(data);
    if (*head == NULL) {
        *head = new_node;
        new_node->next = new_node;
    } else {
        struct Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head;
    }
    size++;
    if (size >= n)
        printf("List is complete\n");
}

// Function to print the elements in the circular linked list
void displayList(struct Node *head) {
    struct Node *temp = head;
    if (head != NULL) {
        do {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != head); // Note the change here
    }
    printf("\n");
}

void josephus(struct Node **head, int n, int k) {
    struct Node *curr = *head;
    struct Node *prev = NULL;
    int count = n;

    if (*head == NULL || k <= 0) {
        printf("Invalid parameters\n");
        return;
    }

    // count the node
    if (*head != NULL) {
        do {
            curr = curr->next;
            size++;
        } while (curr != *head);
    }

    // node limiter
    if (size < n) {
        printf("List is not yet complete\n");
        return;
    }

    // Move to the second node initially
    curr = curr->next;

    // if only single node then print that node and return
    if (n == 1) {
        printf("%d\n", (*head)->data);
        return;
    }

    while (count > 1) {

        // Move curr to the (k-1)th node
        for (int i = 0; i < k - 1; i++) {
            prev = curr;
            curr = curr->next;
        }
        // // remove the kth node
        // prev->next = curr->next;
        // printf("curr is here %d\n", curr->data);
        // printf("value of before head %d\n", prev->data);

        // struct Node *temp = curr;

        // printf("Eliminated %d\n", temp->data);
        // curr = curr->next;
        // prev->next = curr;
        // printf("value of prev now %d\n", prev->data);
        // free(temp);
        // count--;

        // Print and remove the kth node
        printf("Eliminated %d\n", curr->data);
        prev->next = curr->next;
        struct Node *temp = curr;
        curr = curr->next;
        free(temp);

        count--;
    }

    printf("Survivor: %d\n", curr->data);
    *head = curr;
    printf("Remaining list: ");
    displayList(*head);
}

int main() {
    struct Node *head = NULL;
    int data;
    int n, k;
    char op;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter k: ");
    scanf("%d", &k);

    do {

        printf("Op: ");
        scanf(" %c", &op);
        switch (op) {

        case 'a':
            scanf("%d", &data);
            insertEnd(&head, data, n);
            break;

        case 'p':
            displayList(head);
            break;

        case 'j':
            josephus(&head, n, k);
            break;

        case 'x':
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (op != 'x');
    return 0;
}
