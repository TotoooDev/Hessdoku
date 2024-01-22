#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "FileHandler.h"

FILE* openFile(char * name)
{
	FILE* fd = fopen(name, "r");
	assert(fd != NULL);
	return fd;
}

void closeFile(FILE* file)
{
	int res = fclose(file);
	assert(res == 0);
}

// TODO: doc dans le .h
// TODO: handle infinite loop cases
void skipUntil(FILE* fd, char c, int occurences)
{
	char characterRead = ' '; 
	char repetitions = 0;
	while (occurences != 0)
	{
		fread(&characterRead, sizeof(char), 1, fd);
		if (characterRead == c)
		{
			occurences--;
		} 
		
		else if (characterRead == '\'')
		{
			occurences = 0;
		}

		repetitions++;
		if (repetitions == 1000)
		{
			printf("Attention, le formatage du fichier est mauvais !  (attente)");
			exit(EXIT_FAILURE);
		}
	}
}

/* fread version*/
unsigned int readNumbersUntil(FILE* fd, char c)
{
	char characterRead = ' ';
	unsigned int nb = 0;
	int repetitions = 0;

	while (characterRead != c)
	{
		unsigned int size = fread(&characterRead, sizeof(char), 1, fd);
		assert(size == sizeof(char));

		if (characterRead >= '1' && characterRead <= '9')
		{
			nb = nb * 10 + (unsigned int)atoi(&characterRead);
		}

		repetitions++;
		if (repetitions == 10000)
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