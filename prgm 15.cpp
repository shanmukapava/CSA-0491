#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 100
#define MAX_FILES_PER_DIRECTORY 50
#define MAX_FILENAME_LENGTH 50

// Structure to represent a file
struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

// Structure to represent a directory
struct Directory {
    char name[MAX_FILENAME_LENGTH];
    struct File files[MAX_FILES_PER_DIRECTORY];
    int numFiles;
};

// Global array to store directories
struct Directory directories[MAX_DIRECTORIES];
int numDirectories = 0;

// Function prototypes
void createDirectory(char *name);
void createFile(char *dirname, char *filename, int size);
void displayFiles();

int main() {
    // Create some example directories
    createDirectory("docs");
    createDirectory("images");

    // Add files to the directories
    createFile("docs", "file1.txt", 100);
    createFile("docs", "file2.txt", 200);
    createFile("images", "pic1.jpg", 150);
    createFile("images", "pic2.jpg", 250);

    // Display files in the directories
    displayFiles();

    return 0;
}

// Function to create a new directory
void createDirectory(char *name) {
    if (numDirectories < MAX_DIRECTORIES) {
        strcpy(directories[numDirectories].name, name);
        directories[numDirectories].numFiles = 0;
        numDirectories++;
    } else {
        printf("Cannot create directory. Maximum directory limit reached.\n");
    }
}

// Function to create a new file in a directory
void createFile(char *dirname, char *filename, int size) {
    int i;
    for (i = 0; i < numDirectories; i++) {
        if (strcmp(directories[i].name, dirname) == 0) {
            if (directories[i].numFiles < MAX_FILES_PER_DIRECTORY) {
                strcpy(directories[i].files[directories[i].numFiles].name, filename);
                directories[i].files[directories[i].numFiles].size = size;
                directories[i].numFiles++;
                break;
            } else {
                printf("Cannot create file. Maximum file limit reached for directory %s.\n", dirname);
                break;
            }
        }
    }
    if (i == numDirectories) {
        printf("Directory %s not found.\n", dirname);
    }
}

// Function to display all files in all directories
void displayFiles() {
    printf("Files in the directories:\n");
    for (int i = 0; i < numDirectories; i++) {
        printf("Directory: %s\n", directories[i].name);
        printf("Name\t\tSize\n");
        for (int j = 0; j < directories[i].numFiles; j++) {
            printf("%s\t\t%d KB\n", directories[i].files[j].name, directories[i].files[j].size);
        }
    }
}

