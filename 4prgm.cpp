#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int execution_time;
} Process;

// Structure to represent a node in the queue
typedef struct Node {
    Process data;
    struct Node* next;
} Node;

// Structure to represent a queue
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* createNode(Process data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a process
void enqueue(Queue* queue, Process data) {
    Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a process
Process dequeue(Queue* queue) {
    if (queue->front == NULL) {
        Process nullProcess = {-1, -1}; // Assuming -1 as invalid process ID
        return nullProcess;
    }
    Node* temp = queue->front;
    Process data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to select the process with smallest execution time
Process selectProcess(Queue* queue) {
    Node* current = queue->front;
    Process smallest = current->data;
    while (current != NULL) {
        if (current->data.execution_time < smallest.execution_time) {
            smallest = current->data;
        }
        current = current->next;
    }
    return smallest;
}

int main() {
    Queue* queue = createQueue();

    // Example: Enqueueing some processes
    Process p1 = {1, 10};
    Process p2 = {2, 5};
    Process p3 = {3, 8};

    enqueue(queue, p1);
    enqueue(queue, p2);
    enqueue(queue, p3);

    // Example: Selecting and executing the process with smallest execution time
    while (!isEmpty(queue)) {
        Process nextProcess = selectProcess(queue);
        printf("Executing process %d with execution time %d\n", nextProcess.process_id, nextProcess.execution_time);
        dequeue(queue);
    }

    return 0;
}

