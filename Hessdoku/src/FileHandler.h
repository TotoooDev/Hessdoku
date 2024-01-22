#ifndef FILEHANDLER_H
#define FILEHANDLER_H


/**
* Returns a file descriptor for a given file.
* 
* @param name the path to the file
*/
FILE* openFile(char* name);

/**
* Closes a file descriptor
*
* @param name the path to the file
*/
void closeFile(FILE* file);

/**
* Skip characters on the file until c is encountered occurences times.
*/
void skipUntil(FILE* fd, char c, int occurences);

/**
* Reads numbers from the file until c is read.
*/
int readNumbersUntil(FILE* fd, char c);

#endif