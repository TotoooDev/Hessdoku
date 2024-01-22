#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fileHandler.h";


/**
* FILE HANDLER
* 
* This library allows to read a file character by character.
* When a file is open, we place a "cursor" on the first element of the file.
* Then, when the next character is read, the cursor will move past it.
* 
* Considering a FILE, this library will allow to read it easyly, by either advancing the 
* cursor until a given character or read the numbers until a character.
*/



/**
* FILE HANDLER
* 
* This library allows to read a file character by character.
* When a file is open, we place a "cursor" on the first element of the file.
* Then, when the next character is read, the cursor will move past it.
* 
* Considering a FILE, this library will allow to read it easyly, by either advancing the 
* cursor until a given character or read the numbers until a character.
*/


FILE* openFile(const char * name)
{
	FILE* fd = fopen(name, "r");
	assert(fd != NULL);				// Asserts that the file has been opened
	return fd;
}

void closeFile(FILE* file)
{
	int res = fclose(file);
	assert(res == 0);				// Asserts that the file has been closed
}

void skipUntil(FILE* fd, char c, int occurences)
{
	const int maxRepetitions = 1000;

	char characterRead = ' '; 
	int repetitions = 0;		// Infinite loop protection : if code iterates over maxRepetitions times without changes the file is incorrect
	
	// Looping until either c is found or the loop is too long
	while (occurences != 0)
	{
		fread(&characterRead, sizeof(char), 1, fd);
		if (characterRead == c)
		{
			occurences--;
			repetitions = 0;
		} 
		
		// If ' is read, we are at the end of the file !
		else if (characterRead == '\'')
		{
			occurences = 0;
		}

		repetitions++;
		if (repetitions == maxRepetitions)
		{
			printf("Attention, le formatage du fichier est mauvais !  (attente)");
			exit(EXIT_FAILURE);
		}
	}
}

unsigned int readNumbersUntil(FILE* fd, char c)
{
	const int maxRepetitions = 1000;

	char characterRead = ' ';
	unsigned int nb = 0;
	int repetitions = 0;

	// Looping until either c is found or the loop is too long
	while (characterRead != c)
	{
		unsigned int size = fread(&characterRead, sizeof(char), 1, fd);
		assert(size == sizeof(char));

		if (characterRead >= '1' && characterRead <= '9')
		{
			nb = nb * 10 + (unsigned int)atoi(&characterRead);
		}

		repetitions++;
		if (repetitions == maxRepetitions)
		{
			printf("Attention, le formatage du fichier est mauvais ! (lecture d'un nombre)");
			exit(EXIT_FAILURE);
		}
	}

	return nb;
}

/*
char readNext(FILE* fd, char* ignore)
{
	while ()
}
*/

/* A faire pour la bibliotheque et dans grid

  - une fonction readNext, qui permet de lire le prochain caract�re en ignorant tous les caract�res du tableau ignore.
  - Il faudra peut-�tre une fonction qui lit jusqu'� un certain �l�ment (en l'occurence, "|") et, si elle trouve une valeur elle la renvoie sinon elle renvoie 0 ou un truc comme �a
  - une fois cela fait, l'utiliser dans une boucle infinie pour g�n�rer le tableau
*/