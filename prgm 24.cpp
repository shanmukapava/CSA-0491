#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char *filename = "example.txt";
    char buffer[1024];
    int fd;

    // Create a new file
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    write(fd, "Hello, world!\n", 14);

    // Close the file
    close(fd);

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    int bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Display the read data
    printf("Read %d bytes: %s", bytes_read, buffer);

    // Close the file
    close(fd);

    // Delete the file
    if (unlink(filename) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

