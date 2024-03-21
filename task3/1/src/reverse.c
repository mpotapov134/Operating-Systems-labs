#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "utility.h"

void reverse_dir(char* path, char* dst_path, __mode_t mode) {
    DIR* dir_stream = opendir(path);
    if (dir_stream == NULL) {
        opendir_err(errno, path);
        return;
    }

    if (path[strlen(path) - 1] == '/') {
        path[strlen(path) - 1] = 0;
    }

    char* dir_name = get_short_name(path);
    if (is_invalid(dir_name)) {
        printf("Invalid directory name.\n");
        return;
    }

    char* rev_dir_name = reverse_string(dir_name);
    char* next_dst_path = join(dst_path, rev_dir_name, '/');

    mkdir(next_dst_path, mode);
    printf("%s%s -> %s%s\n", HYEL, path, next_dst_path, reset);

    // Reading directory contents
    struct dirent* content;
    while ((content = readdir(dir_stream)) != NULL) {
        if (is_invalid(content->d_name))
            continue;

        char* full_content_name = join(path, content->d_name, '/');

        struct stat content_info;
        stat(full_content_name, &content_info);

        if (S_ISDIR(content_info.st_mode)) {
            reverse_dir(full_content_name, next_dst_path, content_info.st_mode);
        }

        else if (S_ISREG(content_info.st_mode)) {
            make_rev_file(full_content_name, next_dst_path, content_info.st_mode);
        }

        free(full_content_name);
    }

    free(rev_dir_name);
    free(next_dst_path);
    closedir(dir_stream);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Directory name expected.\n");
        return -1;
    }

    struct stat dir_info;
    stat(argv[1], &dir_info);
    reverse_dir(argv[1], ".", dir_info.st_mode);
}
