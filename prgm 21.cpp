#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

// Global array to store memory blocks
struct MemoryBlock memory[MAX_BLOCKS];
int numBlocks = 0;

// Function prototypes
void allocateWorstFit(int id, int size);
void deallocate(int id);
void displayMemory();

int main() {
    // Example memory blocks
    memory[numBlocks++] = (struct MemoryBlock){1, 100, 0};
    memory[numBlocks++] = (struct MemoryBlock){2, 50, 0};
    memory[numBlocks++] = (struct MemoryBlock){3, 200, 0};

    // Display initial memory status
    displayMemory();

    // Example allocations
    allocateWorstFit(4, 75);
    allocateWorstFit(5, 150);

    // Display memory status after allocations
    displayMemory();

    // Example deallocations
    deallocate(2);
    deallocate(3);

    // Display memory status after deallocations
    displayMemory();

    return 0;
}

// Function to allocate memory using Worst Fit strategy
void allocateWorstFit(int id, int size) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < numBlocks; i++) {
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
    } else {
        printf("Memory allocation failed for block with ID %d and size %d: No suitable block found.\n", id, size);
    }
}

// Function to deallocate memory block
void deallocate(int id) {
    for (int i = 0; i < numBlocks; i++) {
        if (memory[i].id == id) {
            memory[i].allocated = 0;
            printf("Memory block with ID %d deallocated successfully.\n", id);
            return;
        }
    }
    printf("Memory deallocation failed: Block with ID %d not found.\n", id);
}

// Function to display memory status
void displayMemory() {
    printf("\nMemory Status:\n");
    printf("ID\tSize\tAllocated\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("%d\t%d\t%s\n", memory[i].id, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
}

