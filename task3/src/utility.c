#include <errno.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

void opendirErr(int errorCode, char* path) {
    switch (errorCode) {
    case EACCES:
        printf("Permission denied.\n");
        break;
    case ENOENT:
        printf("Directory does not exist, or %s is an empty string.\n", path);
        break;
    case ENOTDIR:
        printf("%s is not a directory.", path);
        break;
    default:
        printf("Unknown error.\n");
        break;
    }
}

char* reverseString(char* string) {
    size_t len = strlen(string);
    char* reversed = malloc((len + 1) * sizeof(*reversed));

    for (size_t i = 0; i < len; i++) {
        reversed[i] = string[len - i - 1];
    }
    reversed[len] = 0;
    return reversed;
}

char* getReversedName(char* reversedPath, char* name) {
    char* reversedSubDir = reverseString(name);

    size_t subPathLength = strlen(reversedPath) + strlen(reversedSubDir) + 2;
    char* reversedSubPath = malloc(subPathLength * sizeof(*reversedSubPath));
    int ret = snprintf(reversedSubPath, subPathLength, "%s/%s", reversedPath, reversedSubDir);

    free(reversedSubDir);
    return reversedSubPath;
}

void makeReversedFile(char* fileName, char* reversedFileName) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL)
        return;
    FILE* reversedFile = fopen(reversedFileName, "wb");

    fseek(file, 0, SEEK_END);
    long position = ftell(file);
    for (int i = ftell(file); i > 0; i--) {
        fseek(file, i - 1, SEEK_SET);
        fputc(fgetc(file), reversedFile);
    }

    fclose(file);
    fclose(reversedFile);
}
