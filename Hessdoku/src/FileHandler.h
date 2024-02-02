#ifndef FILEHANDLER_H
#define FILEHANDLER_H


/**
* @return Returns a file extension
*/
int getFileExtension(const char* filename, char* extension);

/**
* Returns a file descriptor for a given file.
* 
* @param name the path to the file
*/
FILE* openFile(const char* name);

/**
* Closes a file descriptor
*
* @param name the path to the file
*/
void closeFile(FILE* file);

/**
* Skip characters on the file until c is encountered a set number of times.
*/
void skipUntil(FILE* fd, char c, int occurences);

/**
* Reads numbers from the file until the character c is read.
*/
unsigned int readNumbersUntil(FILE* fd, char c);

/**
* Reads an integer from the fd
*/
unsigned int readNextInteger(FILE* fd);


#endif