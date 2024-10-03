#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "You must pass the filename you wish to read.");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Could not find file.");
        return 1;
    }

    char *prev = NULL;
    char *line = NULL;
    char *next = NULL;
    size_t next_len = 0;
    ssize_t read;

    // Read the first line
    read = getline(&next, &next_len, file);
    if (read == -1) {
        printf("File is empty\n");
        fclose(file);
        return 0;
    }

    while (1) {
        // Set the new previous
        prev = line;

        // Set the new current
        line = next;

        // Read the new line
        next = NULL;
        next_len = 0;
        read = getline(&next, &next_len, file);

        if (read == -1) {
            break; // End of file
        }
    }

    if (prev != NULL) {
        printf("%s", prev);
    }
    if (line != NULL) {
        printf("%s", line);
    }

    printf("\n");

    // Clean up
    free(prev);
    free(line);
    fclose(file);

    return 0;
}
