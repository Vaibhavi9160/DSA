#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Maximum number of calls the queue can handle

// Structure for circular queue
typedef struct {
    int queue[MAX];
    int front;
    int rear;
} CircularQueue;

// Initialize the queue
void initQueue(CircularQueue *cq) {
    cq->front = -1;
    cq->rear = -1;
}

// Function to add a new call to the queue
void addCall(CircularQueue *cq, int customerID) {
    // Check for overflow
    if ((cq->front == 0 && cq->rear == MAX - 1) || (cq->rear + 1) % MAX == cq->front) {
        printf("Queue Overflow! Cannot add customer ID %d\n", customerID);
        return;
    }

    // If queue is empty
    if (cq->front == -1) {
        cq->front = 0;
        cq->rear = 0;
    } else {
        // Circular increment
        cq->rear = (cq->rear + 1) % MAX;
    }

    cq->queue[cq->rear] = customerID;
    printf("Customer ID %d added to the queue.\n", customerID);
}

// Function to remove a call from the queue (when an agent is free)
void removeCall(CircularQueue *cq) {
    if (cq->front == -1) {
        printf("Queue Underflow! No calls to remove.\n");
        return;
    }

    int removedCustomer = cq->queue[cq->front];
    printf("Customer ID %d removed from the queue.\n", removedCustomer);

    // If only one element was in the queue
    if (cq->front == cq->rear) {
        cq->front = -1;
        cq->rear = -1;
    } else {
        // Circular increment
        cq->front = (cq->front + 1) % MAX;
    }
}

// Function to display the queue
void displayQueue(CircularQueue *cq) {
    if (cq->front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    int i = cq->front;
    while (1) {
        printf("%d ", cq->queue[i]);
        if (i == cq->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Example usage
int main() {
    CircularQueue cq;
    initQueue(&cq);

    addCall(&cq, 101);
    addCall(&cq, 102);
    addCall(&cq, 103);
    addCall(&cq, 104);
    addCall(&cq, 105);  // Queue is full
    addCall(&cq, 106);  // Overflow

    displayQueue(&cq);

    removeCall(&cq);  // Remove 101
    removeCall(&cq);  // Remove 102

    displayQueue(&cq);

    addCall(&cq, 106); // Now we can add after removals
    addCall(&cq, 107);

    displayQueue(&cq);

    return 0;
}

