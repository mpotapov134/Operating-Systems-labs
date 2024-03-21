#ifndef FM_FUNCTIONS_H
#define FM_FUNCTIONS_H

int fm_mkdir(const char* pathname, __mode_t mode);

void fm_ls(const char* pathname);

void fm_rmdir_r(const char* pathname);

#endif
