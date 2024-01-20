#include <Solver.h>

void createBaton(T_Grid grid, unsigned char* b)
{
	for (unsigned int i = 0; i < getGridSize(grid); i++)
	{
		b[i] = 0;
	}
}

bool checkValidityOfRect(T_Grid grid, int minX, int maxX, int minY, int maxY, unsigned char * baton)
{
	for (int i = minX; i < maxX; i++)
	{
		for (int j = minY; j < maxY; j++)
		{
			if (!checkValidityOfCell(baton, getValue(grid, i, j)))
			{
				return false;
			}
		}
	}
	return true;
}

bool checkValidityOfCell(unsigned char * baton, int val)
{
	if (val != 0)
	{
		if (baton[val-1] != 0)
		{
			return false;
		}
		else
		{
			baton[val-1] = 1;
			return true;
		}
	}
	return true;
}

bool checkValidityOfLine(T_Grid grid)
{
	unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
	createBaton(grid, baton);
	for (unsigned int i = 0; i < getGridSize(grid); i++)
	{
		if (!checkValidityOfRect(grid, i, i+1, 0, getGridSize(grid), baton))
		{
			return false;
		}
		createBaton(grid, baton);
	}
	free(baton);
	return true;
}

bool checkValidityOfColumn(T_Grid grid)
{
	unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
	createBaton(grid, baton);
	for (unsigned int i = 0; i < getGridSize(grid); i++)
	{
		if (!checkValidityOfRect(grid, 0, getGridSize(grid), i, i+1, baton))
		{
			return false;
		}
		createBaton(grid, baton);
	}
	free(baton);
	return true;
}

bool checkValidityOfSquare(T_Grid grid)
{
	unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
	createBaton(grid, baton);
	int X = 0;
	int Y = 0;
	for (unsigned int k = 0; k < getGridSize(grid); k++)
	{
		if (!checkValidityOfRect(grid, X, X + getGridSqrtSize(grid), Y, Y + getGridSqrtSize(grid), baton))
		{
			return false;
		}
		Y += getGridSqrtSize(grid);
		if (Y == getGridSize(grid))
		{
			Y = 0;
			X += getGridSqrtSize(grid);
		}
		if (X == getGridSize(grid))
		{
			X = 0;
		}
		createBaton(grid, baton);
	}
	free(baton);
	return true;
}

bool checkValidityOfGrid(T_Grid grid)
{
	return (checkValidityOfLine(grid) && checkValidityOfColumn(grid) && checkValidityOfSquare(grid));
}

bool removeNotesInGridByRows(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	for (unsigned int k = 0; k < getGridSize(grid); k++)	// Checking for each line
	{
		tempCell = getCell(grid, x, k);
		if (tempCell == currentCell) continue;

		// We check if the grid changed after this operation,
		// Using OR operator with the hasChanged value
		
		hasChanged |= unsetNoteCell(tempCell, currentValue);
	}

	return hasChanged;
}

bool removeNotesInGridByColumns(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	for (unsigned int i = 0; i < getGridSize(grid); i++) // Checking for each column
	{
		tempCell = getCell(grid, i, y);
		if (tempCell == currentCell) continue;

		// We check if the grid changed after this operation,
		// Using OR operator with the hasChanged value

		hasChanged |= unsetNoteCell(tempCell, currentValue);
	}

	return hasChanged;
}

bool removeNotesInGridByBlocks(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	int boxRow = x / getGridSqrtSize(grid) * getGridSqrtSize(grid);
	int boxCol = y / getGridSqrtSize(grid) * getGridSqrtSize(grid);
	for (unsigned int m = 0; m < getGridSqrtSize(grid); m++)
	{
		for (unsigned int n = 0; n < getGridSqrtSize(grid); n++)	// Checking for each cell of a m by n block
		{
			tempCell = getCell(grid, boxRow + m, boxCol + n);		// Represents the current cell
			if (tempCell == currentCell) continue;					// We don't modify the current cell's notes

			// We check if the grid changed after this operation,
			// Using OR operator with the hasChanged value

			hasChanged |= unsetNoteCell(tempCell, currentValue);
		}
	}

	return hasChanged;
}

bool removeNotesInGridByZones(T_Grid grid)
{
	bool hasChanged = false;

	for (unsigned int x = 0; x < getGridSize(grid); x++)
	{
		for (unsigned int y = 0; y < getGridSize(grid); y++)
		{
			T_Cell* currentCell = getCell(grid, x, y);
			unsigned int currentValue = getValueOfCell(currentCell);
			
			if (currentValue == 0) continue;

			// We check if the grid changed after those operations,
			// Using OR operators with the hasChanged value
			
			hasChanged |= removeNotesInGridByColumns(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByRows(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByBlocks(grid, currentCell, currentValue, x, y);

		}
	}
	return hasChanged;
}

int howManyTrue(T_Grid grid, unsigned char* baton)
{
	int howMany = 0;
	for (unsigned int r = 0; r < getGridSize(grid); r++)
	{
		if (baton[r] == true)
		{
			howMany += 1;
		}
	}
	return howMany;
}

int coeffBinomial(int k, int n)
{
	int num = 1;
	int deno = 1;

	for (int i = 0; i < k; i++)
	{
		num = num * (n - i);
		deno = deno * (k - i);
	}

	return num / deno;
}

void checkRectKUpletSolve(T_Grid grid, unsigned char* b, int minX, int maxX, int minY, int maxY, int k, unsigned char * variable)
{
	int whichCell = 0;
	for (int i = minX; i < maxX; i++)
	{
		for (int j = minY; j < maxY; j++)
		{
			for (int m = 0; m < k; m++)
			{
				if (getValue(grid, i, j) == variable[m])
				{
					b[whichCell] = true;
				}
			}
			whichCell += 1;
		}
		whichCell += 1;
	}
}

void nextSquare (int step, int* xSquare, int* ySquare)
{
	ySquare += step;
	if (ySquare == step)
	{
		ySquare = 0;
		xSquare += step;
	}
	if (xSquare == step)
	{
		xSquare = 0;
	}
}

bool removeNotesKUpletRows(T_Grid grid,T_Cell ** var, int * variable, int k, int x)
{
	bool hasChanged = false;
	T_Cell* tempCell;
	bool notTheSame = true;

	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int m = 0; m < k; m++)
		{
			tempCell = getCell(grid, x, i);
			if (tempCell == var[m])
			{
				notTheSame = false;
			}
		}
		if (notTheSame)
		{
			for (int j = 0; j < k; j++) {
				hasChanged |= unsetNoteCell(tempCell, variable[j]);
			}
		}
		notTheSame = false;
	}

	return hasChanged;
}

bool removeNotesKUpletColumns(T_Grid grid, T_Cell** var, int* variable, int k, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;
	bool notTheSame = true;

	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int m = 0; m < k; m++)
		{
			tempCell = getCell(grid, i, y);
			if (tempCell == var[m])
			{
				notTheSame = false;
			}
		}
		if (notTheSame)
		{
			for (int j = 0; j < k; j++) {
				hasChanged |= unsetNoteCell(tempCell, variable[j]);
			}
		}
		notTheSame = false;
	}

	return hasChanged;
}

bool removeNotesKUpletSquare(T_Grid grid, T_Cell** var, int* variable, int k, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;
	bool notTheSame = true;
	int sqrtSize = getGridSqrtSize(grid);

	int boxRow = x / sqrtSize * sqrtSize;
	int boxCol = y / sqrtSize * sqrtSize;
	for (unsigned int m = 0; m < sqrtSize; m++)
	{
		for (unsigned int n = 0; n < sqrtSize; n++)
		{	
			for (int m = 0; m < k; m++)
			{
				tempCell = getCell(grid, boxRow + m, boxCol + n);
				if (tempCell == var[m])
				{
					notTheSame = false;
				}
			}
			if (notTheSame)
			{
				for (int j = 0; j < k; j++) {
					hasChanged |= unsetNoteCell(tempCell, variable[j]);
				}
			}
			notTheSame = false;
		}
	}

	return hasChanged;
}

bool removeNoteOnCell(T_Grid grid, T_Cell** var, int* variable, int k)
{
	int size = getGridSize(grid);
	T_Cell* tempCell;
	bool theSame = false;
	bool notTheSame = true;
	bool hasChanged = false;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			tempCell = getCell(grid, i, j);
			for (int m = 0; m < k; m++)
			{
				if (tempCell == var[m])
				{
					theSame = true;
				}
			}
			if (theSame) {
				for (int t = 1; t < 10; t++)
				{
					for (int n = 0; n < k; n++)
					{
						if (t == variable[n])
						{
							notTheSame = false;
						}
					}
					if (notTheSame)
					{
						hasChanged |= unsetNoteCell(tempCell, t);
					}
				}
				theSame = false;
			}
		}
	}
	return hasChanged;
}

int** generateKtuples(int tupleSize, int nbCombinations)
{
	if (tupleSize < 0)
	{
		fprintf(stderr, "Invalid tuple size given (%d)\n", tupleSize);
		return NULL;
	}

	// Calcul du nombre total de combinaisons
	int totalCombinations = 1;
	for (int i = 0; i < tupleSize; i++)
	{
		totalCombinations *= 9 - i;
	}

	// Vérification de la taille demandée par rapport au nombre total de combinaisons possibles
	if (nbCombinations > totalCombinations)
	{
		fprintf(stderr, "Invalid number of combinations requested (%d)\n", nbCombinations);
		return NULL;
	}

	// Allocation du tableau de résultats
	int** tuples = (int**)malloc(nbCombinations * sizeof(int*));
	for (int i = 0; i < nbCombinations; i++)
	{
		tuples[i] = (int*)malloc(nbCombinations * sizeof(int));
	}

	int tupleIndex = 0;

	// Boucle pour générer les combinaisons
	for (int i = 1; i <= 9 && tupleIndex < nbCombinations; i++)
	{
		if (tupleSize == 1)
		{
			tuples[tupleIndex][0] = i;
			tupleIndex++;
			continue;
		}

		for (int j = 2; j <= 9 && tupleIndex < nbCombinations; j++)
		{
			if (tupleSize == 2)
			{
				tuples[tupleIndex][0] = i;
				tuples[tupleIndex][1] = j;
				tupleIndex++;
				continue;
			}

			for (int k = 3; k <= 9 && tupleIndex < nbCombinations; k++)
			{
				if (tupleSize == 3)
				{
					tuples[tupleIndex][0] = i;
					tuples[tupleIndex][1] = j;
					tuples[tupleIndex][2] = k;
					tupleIndex++;
					continue;
				}

				for (int l = 4; l <= 9 && tupleIndex < nbCombinations; l++)
				{
					if (tupleSize == 4)
					{
						tuples[tupleIndex][0] = i;
						tuples[tupleIndex][1] = j;
						tuples[tupleIndex][2] = k;
						tuples[tupleIndex][3] = l;
						tupleIndex++;
					}
				}
			}
		}
	}

	return tuples;
}

// Fonction pour libérer la mémoire allouée au tableau de tuples
void freeTuples(int** tuples, int numTuples)
{
	for (int i = 0; i < numTuples; i++)
	{
		free(tuples[i]);
	}
	free(tuples);
}

bool kUpletsSolve (T_Grid grid, const int k) {

	//TODO
	// - si square est line ou colonne
	// - stopper quand trouver un k_uplet



	bool hasChanged = false;
	int* variable = malloc(sizeof(int) * k);
	T_Cell** cooVariable = malloc(sizeof(T_Cell) * k);

	int size = getGridSize(grid);

	int howManyT = 0;

	unsigned char* baton = malloc(getGridSize(grid) * sizeof(unsigned char));
	int possibility = coeffBinomial(k, size);

	// CODE POUR MONTRER QUE ÇA MARCHE
	int** tuples = generateKtuples(k, possibility);

	if (tuples != NULL)
	{
		printf("Liste de kuplets générés :\n");
		for (int i = 0; i < possibility; i++)
		{
			for (int j = 0; j < k; j++)
			{
				printf("%d ", tuples[i][j]);
			}
			printf("\n");
		}

		// Libérer la mémoire allouée
		freeTuples(tuples, possibility);
	}
	// CODE POUR MONTRER QUE ÇA MARCHE

	printf("%d", possibility);

	int stop = 0;	

	while (stop < possibility && hasChanged == false)
	{
		int xSquare = 0;
		int ySquare = 0;
		int sqrtS = getGridSqrtSize(grid);

		//TODO possibility, faire variable


		// Pour les 27 zones
		
		for (unsigned int i = 0; i < size; i++)
		{

			//SQUARE

			createBaton(grid, baton);

			checkRectKUpletSolve(grid, baton, xSquare, xSquare + sqrtS, ySquare, ySquare + sqrtS, k, variable);

			howManyT = howManyTrue(grid, baton);

			if (howManyT == k)
			{
				//TODO enlever les notes inutiles
				howManyT = 0;
				hasChanged |= removeNotesKUpletSquare(grid, cooVariable, variable, k, xSquare, ySquare);
				hasChanged |= removeNoteOnCell(grid, cooVariable, variable, k);

			}

			nextSquare(getGridSqrtSize(grid), &xSquare, &ySquare);


			// LIGNE
			
			// Pour les k nombres compris entre 1 et 9 (k nombres distincts)
					// Tableau de booléens t de taille 9 tous à faux
			createBaton(grid, baton);

			// Pour les k nombres 
					// Pour les 9 cases d'une zone, si la case contient k[i], t[case] = vrai
			checkRectKUpletSolve(grid, baton, i, i, 0, size, k, variable);

			// Si exactement 3 cases de t sont à true, alors on a un triplet
			howManyT = howManyTrue(grid, baton);
			
			if (howManyT == k)
			{
				howManyT = 0;
				hasChanged |= removeNotesKUpletRows(grid, cooVariable, variable, k, i);
				hasChanged |= removeNoteOnCell(grid, cooVariable, variable, k);
			}


			//COLONNE

			createBaton(grid, baton);

			checkRectKUpletSolve(grid, baton, 0, size, i, i, k, variable);

			howManyT = howManyTrue(grid, baton);

			if (howManyT == k)
			{
				//TODO enlever les notes inutiles
				howManyT = 0;
				hasChanged |= removeNotesKUpletColumns(grid, cooVariable, variable, k, i);
				hasChanged |= removeNoteOnCell(grid, cooVariable, variable, k);
			}

		}

		printf("%d\n", stop);

		stop += 1;
	}

	free(variable);
	free(cooVariable);
	free(baton);
	return hasChanged;
}