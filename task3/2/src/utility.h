#ifndef ERROR_PRINTERS_H_INCLUDED
#define ERROR_PRINTERS_H_INCLUDED

int is_invalid(char* name);

char* join(const char* str1, const char* str2, char symb);

char* concat(const char* str1, const char* str2);

void print_file(FILE* file);

#endif
