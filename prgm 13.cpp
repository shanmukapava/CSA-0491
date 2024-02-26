#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

// Global memory array
struct MemoryBlock memory[MEMORY_SIZE];

// Function prototypes
void initializeMemory();
void displayMemory();
void allocateFirstFit(int id, int size);
void allocateBestFit(int id, int size);
void allocateWorstFit(int id, int size);

int main() {
    initializeMemory();

    // Example allocations
    allocateFirstFit(1, 20);
    allocateFirstFit(2, 10);
    allocateFirstFit(3, 30);

    allocateBestFit(4, 15);
    allocateBestFit(5, 25);
    allocateBestFit(6, 10);

    allocateWorstFit(7, 30);
    allocateWorstFit(8, 25);

    displayMemory();

    return 0;
}

// Initialize memory blocks
void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].id = -1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

// Display memory blocks
void displayMemory() {
    printf("Memory Status:\n");
    printf("ID\tSize\tAllocated\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d\t%d\t%s\n", memory[i].id, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
    printf("\n");
}

// Allocate memory using First Fit strategy
void allocateFirstFit(int id, int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            memory[i].id = id;
            memory[i].allocated = 1;
            break;
        }
    }
}

// Allocate memory using Best Fit strategy
void allocateBestFit(int id, int size) {
    int bestFitIndex = -1;
    int minFragmentation = MEMORY_SIZE + 1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            int fragmentation = memory[i].size - size;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].id = id;
        memory[bestFitIndex].allocated = 1;
    }
}

// Allocate memory using Worst Fit strategy
void allocateWorstFit(int id, int size) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            int fragmentation = memory[i].size - size;
            if (fragmentation > maxFragmentation) {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].id = id;
        memory[worstFitIndex].allocated = 1;
    }
}

