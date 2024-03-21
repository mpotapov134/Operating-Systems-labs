#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "colors.h"
#include "fm_functions.h"

int fm_mkdir(const char* pathname, __mode_t mode) {
    if (mkdir(pathname, mode) == -1) {
        return errno;
    }
    return 0;
}

void fm_ls(const char* pathname) {
    DIR* dir_stream = opendir(pathname);
    if (dir_stream == NULL) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir_stream)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir_stream);
}

void fm_rmdir_r(const char* pathname) {
    DIR* dir_stream = opendir(pathname);
    if (dir_stream == NULL) {
        return;
    }

    // struct dirent *entry;
    // while ((entry = readdir(dir_stream)) != NULL) {
    //     printf("%s\n", entry->d_name);
    // }

    closedir(dir_stream);
    rmdir(pathname);
}
