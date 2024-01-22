#ifndef FILEHANDLER_H
#define FILEHANDLER_H


/**
* Returns a file descriptor usable to read the file.
* 
* @param name the path to the file
*/
FILE* openFile(char* name);

void closeFile(FILE* file);

void skipUntil(FILE* fd, char c, int occurences);

unsigned int readNumbersUntil(FILE* fd, char c);

#endif