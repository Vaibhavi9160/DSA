#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Define structure for tree node
typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

// Queue structure for level-order insertion and traversal
typedef struct Queue {
    Node *arr[MAX];
    int front, rear;
} Queue;

// Queue operations
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Node *node) {
    if (q->rear == MAX - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->arr[++q->rear] = node;
}

Node *dequeue(Queue *q) {
    if (isEmpty(q))
        return NULL;
    Node *temp = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return temp;
}

// Create a new node
Node *createNode(char c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ch = c;
    newNode->freq = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Search if character exists in the tree and increment frequency if found
int incrementIfExists(Node *root, char c) {
    if (!root) return 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node *temp = dequeue(&q);
        if (temp->ch == c) {
            temp->freq++;
            return 1;
        }
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    return 0;
}

// Insert a new character level-wise
Node *insertLevelOrder(Node *root, char c) {
    if (!root)
        return createNode(c);

    // If character exists, increment frequency and return
    if (incrementIfExists(root, c))
        return root;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node *temp = dequeue(&q);

        if (!temp->left) {
            temp->left = createNode(c);
            break;
        } else {
            enqueue(&q, temp->left);
        }

        if (!temp->right) {
            temp->right = createNode(c);
            break;
        } else {
            enqueue(&q, temp->right);
        }
    }
    return root;
}

// Level order traversal to print (char, freq)
void levelOrderPrint(Node *root) {
    if (!root) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node *temp = dequeue(&q);
        printf("(%c, %d) ", temp->ch, temp->freq);

        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
}

// Main function
int main() {
    char str[MAX];
    printf("Enter a string: ");
    scanf("%[^\n]", str);

    Node *root = NULL;

    for (int i = 0; i < strlen(str); i++) {
        // Ignore spaces
        if (str[i] == ' ')
            continue;
        root = insertLevelOrder(root, str[i]);
    }

    printf("\nLevel Order Traversal (Character, Frequency):\n");
    levelOrderPrint(root);
    printf("\n");

    return 0;
}
