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

bool kUpletsSolve(T_Grid grid, const int k) {

	//TODO
	//	- faire des sous fonctions
	//  - optimisation
	//  - finir les TODO 

	bool hasChanged = false;
	int* variable = malloc(sizeof(int) * k);

	int howManyTrue = 0;

	unsigned char* batonL = malloc(getGridSize(grid) * sizeof(unsigned char));
	unsigned char* batonC = malloc(getGridSize(grid) * sizeof(unsigned char));
	int possibility = 0; //TODO calcul
	int stop = 0;

	while(stop != possibility || hasChanged == false)
	{
		//TODO possibility, faire varibale

		// Pour les 27 zones
		// Ligne + colonne
		for (unsigned int i = 0; i < getGridSize(grid); i++)
		{
			// Pour les k nombres compris entre 1 et 9 (k nombres distincts)
					// Tableau de booléens t de taille 9 tous à faux
			createBaton(grid, batonL);
			createBaton(grid, batonC);
			for (unsigned int j = 0; j < getGridSize(grid); j++)
			{
				// Pour les k nombres 
				for (int m = 0; m < k; m++)
				{
					// Pour les 9 cases d'une zone, si la case contient k[i], t[case] = vrai
					if (getValue(grid, i, j) == variable[m])
					{
						batonL[variable[m]] = true;
					}
					if (getValue(grid, j, i) == variable[m])
					{
						batonC[variable[m]] = true;
					}
				}
			}
			// Si exactement 3 cases de t sont à true, alors on a un triplet
			for (unsigned int r = 0; r < getGridSize(grid); r++)
			{
				if (batonL[r] == true)
				{
					howManyTrue += 1;
				}
			}
			if (howManyTrue == 3)
			{
				//TODO enlever les notes inutiles
				howManyTrue = 0;
				hasChanged = true;
			}
			else
			{
				howManyTrue = 0;
				for (unsigned int r = 0; r < getGridSize(grid); r++)
				{
					if (batonC[r] == true)
					{
						howManyTrue += 1;
					}
				}
				if (howManyTrue == 3)
				{
					//TODO enlever les notes inutiles
					howManyTrue = 0;
					hasChanged = true;
				}
			}
		}
		//TODO square
		}

	free(variable);
	free(batonL);
	free(batonC);
	return hasChanged;
}