#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

// Structure to represent a file
struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

// Global array to store files
struct File files[MAX_FILES];
int numFiles = 0;

// Function prototypes
void createFile(char *name, int size);
void displayFiles();

int main() {
    // Create some example files
    createFile("file1.txt", 100);
    createFile("file2.jpg", 200);
    createFile("file3.mp3", 150);

    // Display the files
    displayFiles();

    return 0;
}

// Function to create a new file
void createFile(char *name, int size) {
    if (numFiles < MAX_FILES) {
        strcpy(files[numFiles].name, name);
        files[numFiles].size = size;
        numFiles++;
    } else {
        printf("Cannot create file. Maximum file limit reached.\n");
    }
}

// Function to display all files
void displayFiles() {
    printf("Files in the directory:\n");
    printf("Name\t\tSize\n");
    for (int i = 0; i < numFiles; i++) {
        printf("%s\t\t%d KB\n", files[i].name, files[i].size);
    }
}

