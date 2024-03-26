#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

int is_invalid(char* name) {
    return (name == NULL || name == "" ||
        strcmp(".", name) == 0 || strcmp("..", name) == 0);
}

char* join(const char* str1, const char* str2, char symb) {
    size_t joined_len = strlen(str1) + strlen(str2) + 2;
    char* joined = malloc(joined_len * sizeof(*joined));
    snprintf(joined, joined_len, "%s%c%s", str1, symb, str2);
    return joined;
}

char* concat(const char* str1, const char* str2) {
    size_t res_len = strlen(str1) + strlen(str2) + 1;
    char* res = malloc(res_len * sizeof(*res));
    snprintf(res, res_len, "%s%s", str1, str2);
    return res;
}

void print_file(FILE* file) {
    int buffer_size = 100;
    char* buffer = malloc(buffer_size * sizeof(*buffer));

    while (!feof(file)) {
        int bytes_read = fread(buffer, 1, buffer_size, file);
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fflush(stdout);

    free(buffer);
}
