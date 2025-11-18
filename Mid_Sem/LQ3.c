#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Maximum stack size

// Stack structure
typedef struct {
    char* items[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Push item onto stack
void push(Stack* s, char* item) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->top++;
    s->items[s->top] = strdup(item);  // allocate new string
}

// Pop item from stack
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    char* item = s->items[s->top];
    s->top--;
    return item;
}

// Peek top item
char* peek(Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->items[s->top];
}

// Perform an operation: push to undo stack and clear redo stack
void performOperation(Stack* undo, Stack* redo, char* op) {
    push(undo, op);
    // Clear redo stack
    while (!isEmpty(redo)) {
        free(pop(redo));
    }
    printf("Performed operation: \"%s\"\n", op);
}

// Undo: pop from undo stack and push to redo stack
void undoOperation(Stack* undo, Stack* redo) {
    char* op = pop(undo);
    if (op == NULL) {
        printf("Nothing to undo.\n");
        return;
    }
    push(redo, op);
    printf("Undone. Next operation that can be undone is = \"%s\"\n", peek(undo) ? peek(undo) : "None");
}

// Redo: pop from redo stack and push to undo stack
void redoOperation(Stack* undo, Stack* redo) {
    char* op = pop(redo);
    if (op == NULL) {
        printf("Nothing to redo.\n");
        return;
    }
    push(undo, op);
    printf("Redo completed. Next operation that can be redone is = \"%s\"\n", peek(redo) ? peek(redo) : "None");
}

int main() {
    Stack undo, redo;
    initStack(&undo);
    initStack(&redo);

    performOperation(&undo, &redo, "op1");
    performOperation(&undo, &redo, "op2");
    performOperation(&undo, &redo, "op3");

    undoOperation(&undo, &redo);  // Undo op3
    redoOperation(&undo, &redo);  // Redo op3
    undoOperation(&undo, &redo);  // Undo op3
    undoOperation(&undo, &redo);  // Undo op2

    performOperation(&undo, &redo, "op4");  // Perform new op4
    undoOperation(&undo, &redo);            // Undo op4

    // Free remaining allocated strings
    while (!isEmpty(&undo)) free(pop(&undo));
    while (!isEmpty(&redo)) free(pop(&redo));

    return 0;
}
