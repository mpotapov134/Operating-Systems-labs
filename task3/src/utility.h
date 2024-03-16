#ifndef ERROR_PRINTERS_H_INCLUDED
#define ERROR_PRINTERS_H_INCLUDED

void opendirErr(int errorCode, char* path);

char* reverseString(char* string);

char* getReversedName(char* reversedPath, char* name);

void makeReversedFile(char* fileName, char* reversedFileName);

#endif
