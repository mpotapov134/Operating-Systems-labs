#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "utility.h"

int isCurrentOrParent(char* name) {
    if (strcmp(".", name) == 0 || strcmp("..", name) == 0) {
        return 1;
    }
    return 0;
}

void reverseRecursive(char* path, char* reversedPath) {
    DIR* dirStream = opendir(path);
    if (dirStream == NULL) {
        opendirErr(errno, path);
        return;
    }

    struct dirent* content;
    while ((content = readdir(dirStream)) != NULL) {
        if (isCurrentOrParent(content->d_name))
            continue;

        char fullContentName[255];
        int ret = snprintf(fullContentName, 255, "%s/%s", path, content->d_name);
        struct stat contentInfo;
        stat(fullContentName, &contentInfo);

        if (S_ISDIR(contentInfo.st_mode)) {
            char* reversedSubPath = getReversedName(reversedPath, content->d_name);
            printf("%s%s -> %s\n----", HYEL, fullContentName, reversedSubPath);
            printf("%s", reset);
            mkdir(reversedSubPath, 0777);
            reverseRecursive(fullContentName, reversedSubPath);
            free(reversedSubPath);
        }

        else if (S_ISREG(contentInfo.st_mode)) {
            char* reversedFileName = getReversedName(reversedPath, content->d_name);
            printf("%s%s -> %s\n", HYEL, fullContentName, reversedFileName);
            printf("%s", reset);
            makeReversedFile(fullContentName, reversedFileName);
            free(reversedFileName);
        }
    }
    closedir(dirStream);
}

int main(int argc, char** argv) {
    reverseRecursive(argv[1], argv[1]);
}
