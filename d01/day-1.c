#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
// #include "read_file.h"

static int current_value = 50;
static int password = 0;


/* This code was extracted from one of my other projects available at:
 *     github.com/architmishra-15/c-helpers
 */
typedef struct {
  size_t size;
  char* string;
} FString;

static FString read_file(const char* filename)
{
  FILE* f = fopen(filename, "r");
  int fd = fileno(f);
  if (f == NULL)
  {
    fprintf(stderr, "[ERROR] FILE: Could not open file: %s\n        [ERROR]: %s", filename, strerror(errno));
    fclose(f);
    exit(-1);
  }

  FString data = {0};

  struct stat st = {0};
  fstat(fd, &st);

  data.size = st.st_size;

  data.string = (char*)malloc(data.size+1);
  if (data.string == NULL) // Check malloc success
  {
    fprintf(stderr, "[ERROR] MEMORY: Could not allocate memory\n[TIP]: Buy more RAM Peasant");
    fclose(f);
    exit(-1);
  }

  size_t rd = fread(data.string, 1, data.size, f);

  if (rd != data.size && ferror(f))
  {
    fprintf(stderr, "[ERROR] FILE: Could not read contents of the file: %s\n", filename);
    free(data.string); fclose(f);
    exit(-1);
  }

  data.string[rd] = '\0';
  fclose(f);

  return data;
}


// Checking if character is a delimiter/symbol; that should be its own token
static inline int is_delimiter(char c)
{
  return c == '!' || c == '?' || c == ';' || c == ',' || c == '.' ||
         c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
         c == ':' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/' ||
         c == '<' || c == '>' || c == '&' || c == '|' || c == '#' || c == '@';
}
/* Ends here */

void solution(char c, int val)
{
  if (c == 'L')
  {
    current_value -= val;
    while (current_value < 0) {
      current_value += 100;
    }
  } else {  // 'R'
    current_value += val;
    while (current_value >= 100) current_value -= 100;
  }

  if (current_value == 0) password++;
}

int main(void)
{
  char* filename = "input-1.txt";

  FString content = read_file(filename);

  // Allocate array of pointers to strings
  char** words = (char**)malloc(4578 * sizeof(char*));
  if (words == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
  }

  char* wrd = (char*)malloc(10 * sizeof(char));
  if (wrd == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    free(words);
    return 1;
  }

  size_t count = 0;
  size_t list_count = 0;

  for (size_t i = 0; i < content.size; ++i) {
    if (content.string[i] == '\n') {
      wrd[list_count] = '\0'; // NULL terminated

      words[count] = (char*)malloc((list_count + 1) * sizeof(char));
      strcpy(words[count], wrd);

      count++;
      list_count = 0;
    } else {
      wrd[list_count] = content.string[i];
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
    char direction = wrds[0];  // First character (L or R)
    int value = atoi(&wrds[1]);  // Rest of the string as number

    solution(direction, value);
  }

  printf("Password (times dial pointed at 0): %d\n", password);

  // Cleanup
  for (size_t i = 0; i < count; i++) {
    free(words[i]);
  }
  free(words);
  free(wrd);

  return 0;
}
