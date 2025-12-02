#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int current_value = 50;
static int password = 0;

void solution(char c, int val)
{
    if (c == 'L')
    {
        for (int i = 0; i < val; i++) {
            current_value--;
            if (current_value < 0) {
                current_value = 99;
            }
            if (current_value == 0) password++;
        }
    } else {  // 'R'
        for (int i = 0; i < val; i++) {
            current_value++;
            if (current_value >= 100) {
                current_value = 0;
            }
            if (current_value == 0) password++;
        }
    }
}

int main(void)
{
    char* filename = "input-1.txt";

    // Read file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file!\n");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read entire file into buffer
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Allocate array of pointers to strings
    char** words = (char**)malloc(4578 * sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(buffer);
        return 1;
    }

    char* wrd = (char*)malloc(10 * sizeof(char));
    if (wrd == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(words);
        free(buffer);
        return 1;
    }

    size_t count = 0;
    size_t list_count = 0;

    for (size_t i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n' || buffer[i] == '\0') {
            if (list_count > 0) {
                wrd[list_count] = '\0';
                words[count] = (char*)malloc((list_count + 1) * sizeof(char));
                strcpy(words[count], wrd);
                count++;
                list_count = 0;
            }
        } else {
            wrd[list_count] = buffer[i];
            list_count++;
        }
    }

    if (list_count > 0) {
        wrd[list_count] = '\0';
        words[count] = (char*)malloc((list_count + 1) * sizeof(char));
        strcpy(words[count], wrd);
        count++;
    }

    // Process each word
    for (size_t i = 0; i < count; ++i)
    {
        char* wrds = words[i];
        char direction = wrds[0];
        int value = atoi(&wrds[1]);

        solution(direction, value);
    }

    printf("Password (times dial pointed at 0): %d\n", password);

    // Cleanup
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    free(wrd);
    free(buffer);

    return 0;
}
