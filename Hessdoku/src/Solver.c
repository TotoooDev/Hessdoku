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
		if (baton[r] == 1)
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

void checkRectKUpletSolve(T_Grid grid, unsigned char* bH, int*bN, int minX, int maxX, int minY, int maxY, int k, int * variable)
{
	int whichCell = 0;
	/*printf("\ncheck\n");
	printf("minX : %d\n", minX);
	printf("maxX : %d\n", maxX);
	printf("minY : %d\n", minY);
	printf("maxY : %d\n", maxY);*/
	for (int i = minX; i < maxX; i++)
	{
		//printf("enter x\n");
		for (int j = minY; j < maxY; j++)
		{
			//printf("enter y\n");
			for (int m = 0; m < k; m++)
			{
				if (isNoteInCell(getCell(grid, i, j), variable[m]))
				{
					bH[whichCell] = 1;
					bN[whichCell] -= 1;
				}
			}
			whichCell += 1;
		}
	}
}

void nextSquare (int step, int* xSquare, int* ySquare)
{
	*(ySquare) += step;
	if (*(ySquare) == (step*step))
	{
		*(ySquare) = 0;
		*(xSquare) += step;
	}
	if (*(xSquare) == (step*step))
	{
		*(xSquare) = 0;
	}
}

bool removeNotesKUpletRows(T_Grid grid,int ** cooTuple, int * variable, int k, int x)
{

	bool hasChanged = false;
	bool theSame = false;
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (cooTuple[j][1] == i)
			{
				theSame = true;
			}
		}
		if (!theSame)
		{
			for (int m = 0; m < k; m++)
			{
				hasChanged |= unsetNoteCell(getCell(grid, cooTuple[0][0], i), variable[m]);
			}
		}
		theSame = false;
	}

	return hasChanged;
}

bool removeNotesKUpletColumns(T_Grid grid, int** cooTuple, int* variable, int k, int y)
{
	bool hasChanged = false;
	bool theSame = false;

	/*printf("\nDEBUF\n");
	printf("k : %d\n", k);
	printf("x,y : %d,%d\n", cooTuple[0][0], y);
	printf("variable : %d\n", variable[0]);
	printf("cooTuple : (%d,%d)\n\n", cooTuple[0][0], cooTuple[0][1]);*/

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (cooTuple[j][0] == i)
			{
				theSame = true;
			}
		}
		if (!theSame)
		{
			for (int m = 0; m < k; m++)
			{
				hasChanged |= unsetNoteCell(getCell(grid, i, cooTuple[0][1]), variable[m]);
			}
		}
		theSame = false;
	}

	return hasChanged;
}

bool removeNotesKUpletSquare(T_Grid grid, int** cooTuple, int* variable, int k, int x, int y)
{
	bool hasChanged = false;
	bool theSame = false;

	/*printf("\nDEBUF\n");
	printf("k : %d\n",k);
	printf("x,y : %d,%d\n", x, y);
	printf("variable : %d\n", variable[0]);
	printf("cooTuple : (%d,%d)\n\n", cooTuple[0][0], cooTuple[0][1]);*/

	int sqrtSize = getGridSqrtSize(grid);
	
	for (int i = x; i < x+sqrtSize; i++)
	{
		for (int j = y; j < y+sqrtSize; j++)
		{
			for (int it_k = 0; it_k < k; it_k++)
			{
				if (cooTuple[it_k][0] == i && cooTuple[it_k][1] == j)
				{
					theSame = true;
				}
			}
			//printf("theSame coo (%d,%d) : %d\n", i, y, theSame);
			if (!theSame)
			{
				for (int m = 0; m < k; m++)
				{
					hasChanged |= unsetNoteCell(getCell(grid, i, j), variable[m]);
				}
			}
			theSame = false;
		}
	}

	//printf("\n\n");

	return hasChanged;
}

bool removeNoteOnCell(T_Grid grid, int** cooTuple, int* tuple, int k)
{
	int size = getGridSize(grid);

	bool theSame = false;

	/*printf("\n\n\nDEBUG :\n\n");
	printf("k : %d\nsize : %d\n\n", k,size);*/

	if (k == 1)
	{
		/*printf("coo : (%d,", cooTuple[0][0]);
		printf("%d)\n", cooTuple[0][1]);*/
	}
	if (k == 2)
	{
		/*printf("coo : (%d,", cooTuple[0][0]);
		printf("%d) ; (", cooTuple[0][1]);
		printf("%d,", cooTuple[1][0]);
		printf("%d)\n\n", cooTuple[1][1]);

		printf("var %d %d\n", tuple[0], tuple[1]);*/
	}
	
	bool hasChanged = false;

	for (int w = 0; w < k; w++)
	{
		//printf("boucle w : %d\n", w);
		for (int t = 1; t < size+1; t++)
		{
			//printf("boucle t : %d\n", t);
			for (int r = 0; r < k; r++)
			{
				//printf("boucle r : %d\n", r);
				if (tuple[r] == t)
				{
					//printf("Avant\n");
					//printf("tuple : %d | t : %d\n", tuple[r], t);
					theSame = true;
					
					//printf("Apres\n");
				}
			}
			if (!theSame)
			{
				//printf("rmv : %d\n",t);
				hasChanged |= unsetNoteCell(getCell(grid, cooTuple[w][0], cooTuple[w][1]), t);
			}
			theSame = false;
		}
	}
	
	return hasChanged;
}

int tuplesSize1[][1] = { {1},{2},{3},{4},{5},{6},{7},{8},{9} };
int tuplesSize2[][2] = { {1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8},{2,9},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},{4,5},{4,6},{4,7},{4,8},{4,9},{5,6},{5,7},{5,8},{5,9},{6,7},{6,8},{6,9},{7,8},{7,9},{8,9} };
int tuplesSize3[][3] = { {1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,2,9},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,3,9},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,4,9},{1,5,6},{1,5,7},{1,5,8},{1,5,9},{1,6,7},{1,6,8},{1,6,9},{1,7,8},{1,7,9},{1,8,9},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,3,9},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,4,9},{2,5,6},{2,5,7},{2,5,8},{2,5,9},{2,6,7},{2,6,8},{2,6,9},{2,7,8},{2,7,9},{2,8,9},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,4,9},{3,5,6},{3,5,7},{3,5,8},{3,5,9},{3,6,7},{3,6,8},{3,6,9},{3,7,8},{3,7,9},{3,8,9},{4,5,6},{4,5,7},{4,5,8},{4,5,9},{4,6,7},{4,6,8},{4,6,9},{4,7,8},{4,7,9},{4,8,9},{5,6,7},{5,6,8},{5,6,9},{5,7,8},{5,7,9},{5,8,9},{6,7,8},{6,7,9},{6,8,9},{7,8,9} };
int tuplesSize4[][4] = { {1,2,3,4}, {1,2,3,5},{1,2,3,6},{1,2,3,7},{1,2,3,8},{1,2,3,9},{1,2,4,5},{1,2,4,6},{1,2,4,7},{1,2,4,8},{1,2,4,9},{1,2,5,6},{1,2,5,7},{1,2,5,8},{1,2,5,9},{1,2,6,7},{1,2,6,8},{1,2,6,9},{1,2,7,8},{1,2,7,9},{1,2,8,9},{1,3,4,5},{1,3,4,6},{1,3,4,7},{1,3,4,8},{1,3,4,9},{1,3,5,6},{1,3,5,7},{1,3,5,8},{1,3,5,9},{1,3,6,7},{1,3,6,8},{1,3,6,9},{1,3,7,8},{1,3,7,9},{1,3,8,9},{1,4,5,6},{1,4,5,7},{1,4,5,8},{1,4,5,9},{1,4,6,7},{1,4,6,8},{1,4,6,9},{1,4,7,8},{1,4,7,9},{1,4,8,9},{1,5,6,7},{1,5,6,8},{1,5,6,9},{1,5,7,8},{1,5,7,9},{1,5,8,9},{1,6,7,8},{1,6,7,9},{1,6,8,9},{1,7,8,9},{2,3,4,5},{2,3,4,6},{2,3,4,7},{2,3,4,8},{2,3,4,9},{2,3,5,6},{2,3,5,7},{2,3,5,8},{2,3,5,9},{2,3,6,7},{2,3,6,8},{2,3,6,9},{2,3,7,8},{2,3,7,9},{2,3,8,9},{2,4,5,6},{2,4,5,7},{2,4,5,8},{2,4,5,9},{2,4,6,7},{2,4,6,8},{2,4,6,9},{2,4,7,8},{2,4,7,9},{2,4,8,9},{2,5,6,7},{2,5,6,8},{2,5,6,9},{2,5,7,8},{2,5,7,9},{2,5,8,9},{2,6,7,8},{2,6,7,9},{2,6,8,9},{2,7,8,9},{3,4,5,6},{3,4,5,7},{3,4,5,8},{3,4,5,9},{3,4,6,7},{3,4,6,8},{3,4,6,9},{3,4,7,8},{3,4,7,9},{3,4,8,9},{3,5,6,7},{3,5,6,8},{3,5,6,9},{3,5,7,8},{3,5,7,9},{3,5,8,9},{3,6,7,8},{3,6,7,9},{3,6,8,9},{3,7,8,9},{4,5,6,7},{4,5,6,8},{4,5,6,9},{4,5,7,8},{4,5,7,9},{4,5,8,9},{4,6,7,8},{4,6,7,9},{4,6,8,9},{4,7,8,9},{5,6,7,8},{5,6,7,9},{5,6,8,9},{5,7,8,9},{6,7,8,9} };

/**
* Returns every ktuples (k choose n) of a certain k size.
* 
* @param k The size of the tuples
* @returns A pointer to the ktuples array. Returns NULL if the value is invalid (ie. not between 1 and 4)
* @author Baptiste
*/
int** generateKTuples(const int k, const int size) {
	if (k < 1 || k > 4) {
		printf("Invalid value of k. Supported values are 1, 2, 3, or 4. Was given %d.\n", k);
		return NULL;
	}

	int** tuples = (int**)malloc(size * sizeof(int*));

	if (k == 1) {
		for (int i = 0; i < size; i++) {
			tuples[i] = (int*)malloc(sizeof(int));
			tuples[i][0] = tuplesSize1[i][0];
		}
	}
	else {
		int(*sourceTuple)[4] = (int(*)[4])malloc(size * 4 * sizeof(int));
		int count = 0;

		if (k == 2) {
			int(*source)[2] = tuplesSize2;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < k; j++) {
					sourceTuple[i][j] = source[count][j];
				}
				count++;
			}
		}
		else if (k == 3) {
			int(*source)[3] = tuplesSize3;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < k; j++) {
					sourceTuple[i][j] = source[count][j];
				}
				count++;
			}
		}
		else if (k == 4) {
			int(*source)[4] = tuplesSize4;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < k; j++) {
					sourceTuple[i][j] = source[count][j];
				}
				count++;
			}
		}

		for (int i = 0; i < size; i++) {
			tuples[i] = (int*)malloc(k * sizeof(int));
			for (int j = 0; j < k; j++) {
				tuples[i][j] = sourceTuple[i][j];
			}
		}

		free(sourceTuple);
	}

	return tuples;
}

void afficheBaton(unsigned char * baton)
{
	printf("Baton : ");
	for (int i = 0; i < 9; i++)
	{
		printf("%d ", baton[i]);
	}
	printf("\n");
}

void afficheBatonBis(int* b)
{
	printf("Baton : ");
	for (int i = 0; i < 9; i++)
	{
		printf("%d ", b[i]);
	}
	printf(" \n");
}

void initBaton(T_Grid grid, int* b, int xMin, int xMax, int yMin, int yMax)
{
	int size = getGridSize(grid);

	//printf("test\n");

	for (int z = 0; z < size; z++)
	{
		//printf("test2 %d\n",z);

		b[z] = 0;
	}

	//afficheBatonBis(b);

	int k = 0;

	for (int x = xMin; x < xMax + 1; x++)
	{
		for (int y = yMin; y < yMax + 1; y++)
		{
			for (int i = 1; i < size+1; i++)
			{
				if (isNoteInCell(getCell(grid, x, y), i))
				{
					//printf("cell (%d,%d) : ", x, y);
					//printf("%d \n", i);
					b[k] += 1;
				}
			}
			k++;
		}
	}

	//afficheBatonBis(b);
}

int howManyZero(T_Grid grid, int* b)
{
	int res = 0;
	for (int i = 0; i < getGridSize(grid); i++)
	{
		if (b[i] == 0)
		{
			res++;
		}
	}
	return res;
}

void findCooTupleSquare(int sqrtS, unsigned char * b, int** coo, int addX, int addY)
{
	int count = 0;
	int count2 = 0;
	for (int i = 0; i < sqrtS; i++)
	{
		for (int j = 0; j < sqrtS; j++)
		{
			if (b[count] == 1)
			{
				coo[count2][0] = addX + i;
				coo[count2][1] = addY + j;
				count2++;
			}
			count++;
		}
	}
}

bool kUpletsSolve (T_Grid grid, const int k) {

	bool hasChanged = false;

	int howManyT = 0;
	int howManyZ = 0;

	int stop = 0;
	int stopbis = 0;

	int size = getGridSize(grid);

	int* variable = malloc(sizeof(int) * k);
	int** cooTuple = malloc(sizeof(int*) * k);

	for (int i = 0; i < k; i++)
	{
		cooTuple[i] = malloc(sizeof(int) * 2);
	}

	unsigned char* batonHidden = malloc(size * sizeof(unsigned char));
	int* batonNaked = malloc(size * sizeof(int));

	int possibility = coeffBinomial(k, size);
	
	//printf("\nbefore\n");
	int** tuples = generateKTuples(k, possibility);
	//printf("\nafter\n");

	while (stop < possibility && !hasChanged)
	{
		int xSquare = 0;
		int ySquare = 0;
		int sqrtS = getGridSqrtSize(grid);

		//printf("\ntest\n");
		for (int i = 0; i < k; i++) {
			/*printf("k : %d\n", k);
			printf("i : %d\n", i);
			printf("stop : %d\n", stop);
			printf("tuples[stop][i] : %d\n", tuples[stop][i]);*/
			variable[i] = tuples[stop][i];
		}
		//printf("\ntest1\n");

		/*if (k == 1)
		{
			printf("\n\nTesting %d...\n",variable[0]);
		}
		if (k == 2)
		{
			printf("\n\nTesting %d %d...\n", variable[0], variable[1]);
		}*/
		
		while (stopbis < size && hasChanged == false)
		{

			//SQUARE

			//printf("Square %d %d\n", xSquare, ySquare);

			createBaton(grid, batonHidden);
			initBaton(grid, batonNaked, xSquare, xSquare + sqrtS - 1, ySquare, ySquare + sqrtS - 1);

			checkRectKUpletSolve(grid, batonHidden, batonNaked, xSquare, xSquare + sqrtS, ySquare, ySquare + sqrtS, k, variable);

			howManyT = howManyTrue(grid, batonHidden);
			howManyZ = howManyZero(grid, batonNaked);

			if (howManyT == k)
			{
				//printf("\nHERE !\n");

				//afficheBaton(batonHidden);

				//findCooTupleSquare(sqrtS, batonHidden, cooTuple, xSquare, ySquare);

				int bwa = 0;
				int beh = 0;
				for (int i = 0; i < sqrtS; i++)
				{
					for (int j = 0; j < sqrtS; j++)
					{
						if (batonHidden[bwa] == 1)
						{
							cooTuple[beh][0] = xSquare + i;
							cooTuple[beh][1] = ySquare + j;
							beh++;
						}
						bwa++;
					}
				}
				
				howManyT = 0;
				
				hasChanged |= removeNoteOnCell(grid, cooTuple, variable, k);
				//printf("on cell : ");
				if (hasChanged) {
					//printf("Change occur !\n");
				}
				else {
					//printf("No change !\n");
				}

			}
			if (howManyZ == k && !hasChanged)
			{
				//printf("bouh\n");
				howManyZ = 0;

				int bwa = 0;
				int beh = 0;
				for (int i = 0; i < sqrtS; i++)
				{

					for (int j = 0; j < sqrtS; j++)
					{
						if (batonNaked[bwa] == 0)
						{
							cooTuple[beh][0] = xSquare + i;
							cooTuple[beh][1] = ySquare + j;
							beh++;
						}
						bwa++;
					}
				}

				//printf("\nk : %d\n", k);

				hasChanged |= removeNotesKUpletSquare(grid, cooTuple, variable, k, xSquare, ySquare);
				//printf("everywher : ");
				if (hasChanged) {
					//printf("Change occur !\n");
				}
				else {
					//printf("No change !\n");
				}
			}

			nextSquare(getGridSqrtSize(grid), &xSquare, &ySquare);

			//printf("\nfin square hasChanged : %d\n", hasChanged);

			// LIGNE

			//printf("Line %d\n", stopbis);
			
			if (!hasChanged)
			{
				//printf("testLine\n");
				// Pour les k nombres compris entre 1 et 9 (k nombres distincts)
						// Tableau de bool�ens t de taille 9 tous � faux
				createBaton(grid, batonHidden);
				//printf("avant\n");
				initBaton(grid, batonNaked, stopbis, stopbis, 0, size-1);
				//printf("apr�s\n");

				// Pour les k nombres 
						// Pour les 9 cases d'une zone, si la case contient k[i], t[case] = vrai
				checkRectKUpletSolve(grid, batonHidden, batonNaked, stopbis, stopbis+1, 0, size, k, variable);

				// Si exactement 3 cases de t sont � true, alors on a un triplet
				howManyT = howManyTrue(grid, batonHidden);
				howManyZ = howManyZero(grid, batonNaked);

				if (howManyT == k)
				{
					//printf("HERE !\n");

					int grr = 0;
					for (int i = 0; i < size; i++)
					{
						if (batonHidden[i] == 1)
						{
							cooTuple[grr][0] = stopbis;
							cooTuple[grr][1] = i;
							grr++;
						}
					}

					
					hasChanged |= removeNoteOnCell(grid, cooTuple, variable, k);
				}
				if (howManyZ == k && !hasChanged)
				{
					int grr = 0;
					for (int i = 0; i < size; i++)
					{
						if (batonNaked[i] == 0)
						{
							cooTuple[grr][0] = stopbis;
							cooTuple[grr][1] = i;
							grr++;
						}

					}
					
					hasChanged |= removeNotesKUpletRows(grid, cooTuple, variable, k, stopbis);
				}
				howManyT = 0;
			}

			//printf("\nfin line hasChanged : %d\n", hasChanged);
			//COLONNE


			//printf("Colonne %d\n", stopbis);

			if (!hasChanged)
			{
				//printf("testColonne\n");
				createBaton(grid, batonHidden);
				initBaton(grid, batonNaked, 0, size-1, stopbis, stopbis);

				checkRectKUpletSolve(grid, batonHidden, batonNaked, 0, size, stopbis, stopbis+1, k, variable);

				howManyT = howManyTrue(grid, batonHidden);
				howManyZ = howManyZero(grid, batonNaked);

				//afficheBatonBis(batonNaked);

				if (howManyT == k)
				{
					//TODO enlever les notes inutiles

					int graou = 0;
					for (int i = 0; i < size; i++)
					{
						if (batonHidden[i] == 1)
						{
							cooTuple[graou][1] = stopbis;
							cooTuple[graou][0] = i;
							graou++;
						}
					}
					graou = 0;

					howManyT = 0;
					
					hasChanged |= removeNoteOnCell(grid, cooTuple, variable, k);
				}
				if (howManyZ == k && !hasChanged)
				{
					int graou = 0;
					for (int i = 0; i < size; i++)
					{
						if (batonNaked[i] == 0)
						{
							cooTuple[graou][1] = stopbis;
							cooTuple[graou][0] = i;
							graou++;
						}
					}
					graou = 0;
					howManyT = 0;
					hasChanged |= removeNotesKUpletColumns(grid, cooTuple, variable, k, stopbis);
				}
			}

			stopbis++;

		}

		stopbis = 0;

		stop += 1;
	}

	free(variable);
	free(cooTuple);
	free(batonHidden);
	free(batonNaked);
	// freeTuples(tuples, possibility);

	return hasChanged;
}




void testBouh(T_Grid grid) {
	for (int j = 0; j < 9; j++) {
		printf("\nTest %d : ", j);
		for (int i = 0; i < 9; i++) {
			if (isNoteInCell(getCell(grid, j, i), 1)) {
				printf("o ");
			}
			else {
				printf("x ");
			}
		}
		printf("\n");
	}
}

void testMwah(T_Grid grid) {
	int xSquare = 0;
	int ySquare = 0;
	for (int k = 0; k < 9; k++) {
		printf("\nTest square (%d,%d) : ", xSquare, ySquare);
		for (int i = xSquare; i < xSquare + 3; i++) {
			for (int j = ySquare; j < ySquare + 3; j++) {
				//printf("(%d,%d) ", i, j);
				if (isNoteInCell(getCell(grid, i, j), 1)) {
					printf("o ; ");
				}
				else {
					printf("x ; ");
				}
			}
		}
		nextSquare(3, &xSquare, &ySquare);
	}
}