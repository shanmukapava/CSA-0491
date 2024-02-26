#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char buffer[1024];

    // Create a new file and write data to it
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Hello, world!\n");
    fprintf(file, "This is a test file.\n");

    fclose(file);
    printf("File created and data written successfully.\n");

    // Read data from the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    printf("\nContents of the file:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    // Delete the file
    if (remove(filename) == -1) {
        perror("remove");
        exit(EXIT_FAILURE);
    }
    printf("\nFile deleted successfully.\n");

    return 0;
}

