#include <errno.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "utility.h"

int is_invalid(char* name) {
    return (name == NULL || name == "" ||
        strcmp(".", name) == 0 || strcmp("..", name) == 0);
}

void opendir_err(int errorCode, char* path) {
    switch (errorCode) {
    case EACCES:
        printf("Permission denied.\n");
        break;
    case ENOENT:
        printf("Directory does not exist, or \"%s\" is an empty string.\n", path);
        break;
    case ENOTDIR:
        printf("\"%s\" is not a directory.\n", path);
        break;
    default:
        printf("Unknown error.\n");
        break;
    }
}

char* reverse_string(char* string) {
    size_t len = strlen(string);
    char* reversed = malloc((len + 1) * sizeof(*reversed));

    for (size_t i = 0; i < len; i++) {
        reversed[i] = string[len - i - 1];
    }
    reversed[len] = 0;
    return reversed;
}

char* join(char* str1, char* str2, char symb) {
    size_t joined_len = strlen(str1) + strlen(str2) + 2;
    char* joined = malloc(joined_len * sizeof(*joined));
    snprintf(joined, joined_len, "%s%c%s", str1, symb, str2);
    return joined;
}

static void reverse_array(char* buff, int len) {
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = buff[i];
        buff[i] = buff[j];
        buff[j] = tmp;
    }
}

static void rev_file_content(FILE* src, FILE* dst) {
    int buff_size = 100;
    char* buff = malloc(buff_size * sizeof(*buff));

    fseek(src, 0, SEEK_END);
    long length = ftell(src);
    int iter = length / buff_size;
    int remainder = length - buff_size * iter;

    for (int i = 1; i <= iter; i++) {
        fseek(src, -(buff_size * i), SEEK_END);
        fread(buff, 1, buff_size, src);
        reverse_array(buff, buff_size);
        fwrite(buff, 1, buff_size, dst);
    }

    fseek(src, 0, SEEK_SET);
    fread(buff, 1, remainder, src);
    reverse_array(buff, remainder);
    fwrite(buff, 1, remainder, dst);

    free(buff);
}

void make_rev_file(char* file_name, char* dst_path, __mode_t mode) {
    char* short_name = get_short_name(file_name);
    if (is_invalid(short_name)) {
        return;
    }
    char* rev_name = reverse_string(short_name);
    char* full_rev_name = join(dst_path, rev_name, '/');

    printf("%s%s -> %s%s\n", HYEL, file_name, full_rev_name, reset);

    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        return;
    }
    FILE* rev_file = fopen(full_rev_name, "wb");

    rev_file_content(file, rev_file);

    fclose(file);
    fclose(rev_file);

    chmod(full_rev_name, mode);

    free(rev_name);
    free(full_rev_name);
}

char* get_short_name(char* full_name) {
    char* name = strrchr(full_name, '/');
    if (name == NULL) {
        return full_name;
    }
    return name + 1;
}
