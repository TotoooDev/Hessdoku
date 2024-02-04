#include <Solver.h>


bool removeNotesInGridByRows(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	for (unsigned int k = 0; k < getGridSize(grid); k++)	// Checking for each line
	{
		tempCell = getCell(grid, x, k);
		if (tempCell == currentCell)
			continue;

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
		if (tempCell == currentCell)
			continue;

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
			if (tempCell == currentCell)							// We don't modify the current cell's notes
				continue;					

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
			
			if (currentValue == 0)
				continue;

			// We check if the grid changed after those operations,
			// Using OR operators with the hasChanged value
			
			hasChanged |= removeNotesInGridByColumns(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByRows(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByBlocks(grid, currentCell, currentValue, x, y);

		}
	}
	return hasChanged;
}

/**
* Count how many true there are in an array
* 
* @param grid : the sudoku grid
* @param baton : an array of unsigned char (bool) where we count the true
* 
* @return How many true there are in baton
* 
* @author Marie
*/
int howManyTrue(int size, unsigned char* baton)
{
	int nbValuesToTrue = 0;

	for (unsigned int r = 0; r < size; r++)
		if (baton[r] == 1)
			nbValuesToTrue += 1;

	return nbValuesToTrue;
}

/**
* calculating the binomial coefficient of two values
* 
* @param k
* @param n
* 
* @return the result
* 
* @author Marie
*/
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

/**
* Verify if there is a k-uplet in zone
* 
* @param grid : the sudoku grid
* @param bH : an array to search the hidden k-uplet
* @param bN : an array to search the naked k-uplet
* @param xMin : minimum x of the zone
* @param xMax : maximum x of the zone
* @param yMin : minimum y of the zone
* @param yMax : maximum y of the zone
* @param k : the number of element of the k-uplet
* @param variable : an array with the element of the k-uplet (ex: for the 3-uplet (1, 2, 3) -> [1,2,3])
* 
* @author Marie
*/
void checkRectKUpletSolve(T_Grid grid, unsigned char* bH, int*bN, int minX, int maxX, int minY, int maxY, int k, int* variable)
{
	int whichCell = 0;

	for (int i = minX; i < maxX; i++)
	{
		for (int j = minY; j < maxY; j++)
		{
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

/**
* Calculating the next coordinate of the square in the grid
* 
* @param step : the size of a square
* @param xSquare : the current coordinate x of the square
* @param ySquare : the current coordinate y of the square
* 
* @author Marie
*/
void nextSquare (int step, int* xSquare, int* ySquare)
{
	*(ySquare) += step;

	if (*(ySquare) == (step * step))
	{
		*(ySquare) = 0;
		*(xSquare) += step;
	}
	if (*(xSquare) == (step * step))
		*(xSquare) = 0;
}

/**
* Remove notes on a rows given a k-uplet
* 
* @param grid : the sudoku grid
* @param coordsTuple : the coordinate of the k-uplet
* @param variable : the k-uplet
* @param k : the k of k-uplet
* @param x : the coordinate of the row
* 
* @return true if the grid has changed or else false
* 
* @author Marie
*/
bool removeNotesKUpletRows(T_Grid grid, int** coordsTuple, int* variable, int k, int x, unsigned char** noteRemoved, int** cooNoteRemoved)
{
	bool hasChanged = false;
	bool tempoHasChanged = false;
	bool theSame = false;
	int count = 0;
	
	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int j = 0; j < k; j++)
			if (coordsTuple[j][1] == i)
				theSame = true;

		if (!theSame)
			for (int m = 0; m < k; m++)
			{
				tempoHasChanged = unsetNoteCell(getCell(grid, x, i), variable[m]);
				if (tempoHasChanged)
				{
					noteRemoved[count][variable[m]-1] = 1;
					cooNoteRemoved[count][0] = x;
					cooNoteRemoved[count][1] = i;
				}
				hasChanged |= tempoHasChanged;
				tempoHasChanged = false;
			}

		count += 1;
		theSame = false;
	}

	return hasChanged;
}

/**
* Remove notes on a column given a k-uplet
*
* @param grid : the sudoku grid
* @param cooTuple : the coordinate of the k-uplet
* @param variable : the k-uplet
* @param k : the k of k-uplet
* @param y : the coordinate of the column
*
* @return true if the grid has changed or else false
*
* @author Marie
*/
bool removeNotesKUpletColumns(T_Grid grid, int** cooTuple, int* variable, int k, int y, unsigned char** noteRemoved, int** cooNoteRemoved)
{
	bool hasChanged = false;
	bool tempoHasChanged = false;
	bool theSame = false;
	int count = 0;

	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int j = 0; j < k; j++)
			if (cooTuple[j][0] == i)
				theSame = true;

		if (!theSame)
			for (int m = 0; m < k; m++)
			{
				tempoHasChanged = unsetNoteCell(getCell(grid, i, y), variable[m]);
				if (tempoHasChanged)
				{
					noteRemoved[count][variable[m]-1] = 1;
					cooNoteRemoved[count][0] = i;
					cooNoteRemoved[count][1] = y;
				}
				hasChanged |= tempoHasChanged;
				tempoHasChanged = false;
			}

		count += 1;
		theSame = false;
	}

	return hasChanged;
}

/**
* Remove notes on a square given a k-uplet
*
* @param grid : the sudoku grid
* @param cooTuple : the coordinate of the k-uplet
* @param variable : the k-uplet
* @param k : the k of k-uplet
* @param x : the coordinate x of the first cell of the square
* @param y : the coordinate y of the first cell of the square
*
* @return true if the grid has changed or else false
*
* @author Marie
*/
bool removeNotesKUpletSquare(T_Grid grid, int** coordinatesTuple, int* variable, int k, int x, int y, unsigned char** noteRemoved, int** cooNoteRemoved)
{
	bool hasChanged = false;
	bool tempoHasChanged = false;
	bool theSame = false;
	int count = 0;

	int sqrtSize = getGridSqrtSize(grid);
	
	for (int i = x; i < x + sqrtSize; i++)
	{
		for (int j = y; j < y + sqrtSize; j++)
		{
			for (int it_k = 0; it_k < k; it_k++)
				if (coordinatesTuple[it_k][0] == i && coordinatesTuple[it_k][1] == j)
					theSame = true;

			if (!theSame)
				for (int m = 0; m < k; m++)
				{
					tempoHasChanged = unsetNoteCell(getCell(grid, i, j), variable[m]);
					if (tempoHasChanged)
					{
						noteRemoved[count][variable[m]-1] = 1;
						cooNoteRemoved[count][0] = i;
						cooNoteRemoved[count][1] = j;
					}
					hasChanged |= tempoHasChanged;
					tempoHasChanged = false;
				}

			count += 1;
			theSame = false;
		}
	}

	return hasChanged;
}

/**
* Remove notes on the cell where is the k-uplet
*
* @param grid : the sudoku grid
* @param cooTuple : the coordinate of the k-uplet
* @param tuple : the k-uplet
* @param k : the k of k-uplet
*
* @return true if the grid has changed or else false
*
* @author Marie
*/
bool removeNoteOnCell(T_Grid grid, int** cooTuple, int* tuple, int k, unsigned char** noteRemoved, int** cooNoteRemoved)
{
	int size = getGridSize(grid);
	int count = 0;

	bool theSame = false;
	bool hasChanged = false;
	bool tempoHasChanged = false;

	for (int w = 0; w < k; w++)
	{
		for (int t = 1; t < size+1; t++)
		{
			for (int r = 0; r < k; r++)
				if (tuple[r] == t)
					theSame = true;

			if (!theSame)
			{
				tempoHasChanged = unsetNoteCell(getCell(grid, cooTuple[w][0], cooTuple[w][1]), t);
				if (tempoHasChanged)
				{
					noteRemoved[count][t-1] = 1;
					cooNoteRemoved[count][0] = cooTuple[w][0];
					cooNoteRemoved[count][1] = cooTuple[w][1];
				}
				hasChanged |= tempoHasChanged;
				tempoHasChanged;
			}
			theSame = false;
		}
		count += 1;
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
* 
* @returns A pointer to the ktuples array. Returns NULL if the value is invalid (ie. not between 1 and 4)
* 
* @author Baptiste
*/
int** generateKTuples(const int k, const int size) {

	if (k < 1 || k > 4)
	{
		printf("Invalid value of k. Supported values are 1, 2, 3, or 4. Was given %d.\n", k);
		return NULL;
	}

	int** tuples = (int**)malloc(size * sizeof(int*));

	if (k == 1)
	{
		for (int i = 0; i < size; i++)
		{
			tuples[i] = (int*)malloc(sizeof(int));
			tuples[i][0] = tuplesSize1[i][0];
		}
	}
	else 
	{
		int(*sourceTuple)[4] = (int(*)[4])malloc(size * 4 * sizeof(int));
		int count = 0;

		if (k == 2)
		{
			int(*source)[2] = tuplesSize2;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < k; j++)
					sourceTuple[i][j] = source[count][j];
				count++;
			}
		}
		else if (k == 3)
		{
			int(*source)[3] = tuplesSize3;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < k; j++)
					sourceTuple[i][j] = source[count][j];
				count++;
			}
		}
		else if (k == 4) 
		{
			int(*source)[4] = tuplesSize4;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < k; j++)
					sourceTuple[i][j] = source[count][j];
				count++;
			}
		}

		for (int i = 0; i < size; i++)
		{
			tuples[i] = (int*)malloc(k * sizeof(int));
			for (int j = 0; j < k; j++)
				tuples[i][j] = sourceTuple[i][j];
		}

		free(sourceTuple);
	}

	return tuples;
}

void freeTuples(int** tuples, int tupleSize) {

	for (int i = 0; i < tupleSize; i++)
		free(tuples[i]);				// Frees every member of the i-th tuple

	free(tuples);
}

/* only for debug : display an unsigned char (aka bool) of int of size 9 */
void afficheBaton(unsigned char* baton)
{
	printf("Baton : ");
	for (int i = 0; i < 9; i++)
		printf("%d ", baton[i]);

	printf("\n");
}

/* only for debug : display an array of int of size 9 */
void afficheBatonBis(int* b)
{
	printf("Baton : ");
	for (int i = 0; i < 9; i++)
		printf("%d ", b[i]);

	printf(" \n");
}

/**
* Initialize an array of int with the number of notes on each cell of a zone
* 
* @param grid : the sudoku grid
* @param b : the array of int
* @param xMin : minimum x of the zone
* @param xMax : maximum x of the zone
* @param yMin : minimum y of the zone
* @param yMax : maximum y of the zone
* 
* @author Marie
*/
void initBaton(T_Grid grid, int* b, int xMin, int xMax, int yMin, int yMax)
{
	int size = getGridSize(grid);

	for (int z = 0; z < size; z++)
		b[z] = 0;

	int k = 0;

	for (int x = xMin; x < xMax + 1; x++)
	{
		for (int y = yMin; y < yMax + 1; y++)
		{
			for (int i = 1; i < size + 1; i++)
				if (isNoteInCell(getCell(grid, x, y), i))
					b[k] += 1;

			k++;
		}
	}
}

/**
* Initialize an array of coordinate to (-1,-1)
*
* @param size : the size of the array
* @param coords : the array of coordinate
*
* @author Marie
*/
void initCoordinate(int size, int** coords)
{
	for (int i = 0; i < size; i++)
	{
		coords[i][0] = -1;
		coords[i][1] = -1;
	}
}

/**
* Count how many 0 there are in b
* 
* @param grid : the sudoku grid
* @param b : an array of int
* 
* @return the amount of 0 there are in b
* 
* @author Marie
*/
int howManyZero(T_Grid grid, int* b)
{
	int res = 0;
	for (int i = 0; i < getGridSize(grid); i++)
		if (b[i] == 0)
			res++;

	return res;
}

/**
 * Find the coordinate of the (hidden) k-uplet in a square.
 *
 * @param sqrtS : the square root of the size of the grid
 * @param b : an array of bool (=unsigned char), if it's true (=1) it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addX : the coordinate x of the first cell of the square were the k-uplet is
 * @param addY : the coordinate y of the first cell of the square were the k-uplet is
 *
 * @author Marie
 */
void findCooTupleSquareHidden(int sqrtS, unsigned char* b, int** coords, int addX, int addY)
{
	int count = 0;
	int count2 = 0;
	for (int i = 0; i < sqrtS; i++)
	{
		for (int j = 0; j < sqrtS; j++)
		{
			if (b[count] == 1)
			{
				coords[count2][0] = addX + i;
				coords[count2][1] = addY + j;
				count2++;
			}
			count++;
		}
	}
}

/**
 * Find the coordinate of the (naked) k-uplet in square.
 *
 * @param sqrtS : the square root of the size of the grid
 * @param b : an array of int, if it's a 0 it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addX : the coordinate x of the first cell of the square were the k-uplet is
 * @param addY : the coordinate y of the first cell of the square were the k-uplet is
 *
 * @author Marie
 */
void findCooTupleSquareNaked(int sqrtS, int* b, int** coo, int addX, int addY)
{
	int count = 0;
	int count2 = 0;
	for (int i = 0; i < sqrtS; i++)
	{
		for (int j = 0; j < sqrtS; j++)
		{
			if (b[count] == 0)
			{
				coo[count2][0] = addX + i;
				coo[count2][1] = addY + j;
				count2++;
			}
			count++;
		}
	}
}

/**
 * Find the coordinate (y) of the (hidden) k-uplet in a line.
 *
 * @param size : the size of the array b
 * @param b : an array of bool (=unsigned char), if it's true (=1) it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addX : the coordinate x of the k-uplet
 *
 * @author Marie
 */
void findCooTupleLineHidden(int size, unsigned char* b, int** coo, int addX)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (b[i] == 1)
		{
			coo[count][0] = addX;
			coo[count][1] = i;
			count++;
		}
	}
}

/**
 * Find the coordinate (y) of the (naked) k-uplet in a line.
 *
 * @param size : the size of the array b
 * @param b : an array of int, if it's a 0 it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addX : the coordinate x of the k-uplet
 *
 * @author Marie
 */
void findCooTupleLineNaked(int size, int* b, int** coo, int addX)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (b[i] == 0)
		{
			coo[count][0] = addX;
			coo[count][1] = i;
			count++;
		}
	}
}

/**
 * Find the coordinate (x) of the (hidden) k-uplet in a column.
 *
 * @param size : the size of the array b
 * @param b : an array of bool (=unsigned char), if it's true (=1) it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addY : the coordinate y of the k-uplet
 *
 * @author Marie
 */
void findCooTupleColumnHidden(int size, unsigned char* b, int** coo, int addY)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (b[i] == 1)
		{
			coo[count][1] = addY;
			coo[count][0] = i;
			count++;
		}
	}
}

/**
 * Find the coordinate (x) of the (naked) k-uplet in a column.
 *
 * @param size : the size of the array b
 * @param b : an array of int, if it's a 0 it's an element of the k-uplet
 * @param coo : a matrix where we put the coordinate of the k-uplet
 * @param addY : the coordinate y of the k-uplet
 *
 * @author Marie
 */
void findCooTupleColumnNaked(int size, int* b, int** coo, int addY)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (b[i] == 0)
		{
			coo[count][1] = addY;
			coo[count][0] = i;
			count++;
		}
	}
}

int countNbCoords(int** coordsNoteRemoved)
{
	int res = 0;
	for (int i = 0; i < 9; i++)
	{
		if (coordsNoteRemoved[i][0] != -1)
			res += 1;
	}
	return res;
}

/* TODO: documenter... */
void writeInDoc(int** coordsTuple, int* variable, FILE* outputFile, const char* info1, const char* info2, int k, unsigned char** noteRemoved, int** coordsNoteRemoved)
{
	fprintf(outputFile, "Found a %d-uplet %s on a %s : {%d", k, info1, info2, variable[0]);

	for (int i = 1; i < k; i++)
		fprintf(outputFile, ", %d", variable[i]);

	fprintf(outputFile, "} at coordinates (%d,%d)", coordsTuple[0][0], coordsTuple[0][1]);

	for (int i = 1; i < k; i++)
		fprintf(outputFile, " ; (%d,%d)", coordsTuple[i][0], coordsTuple[i][1]);

	fprintf(outputFile, "\n");

	int howManyCell = countNbCoords(coordsNoteRemoved);
	int howManyNumber = 0;
	int countCell = 0;
	int countNumber = 0;

	for (int i = 0; i < howManyCell; i++)
	{
		while (coordsNoteRemoved[countCell][0] == -1)
			countCell += 1;

		howManyNumber = howManyTrue(9, noteRemoved[countCell]);

		while (noteRemoved[countCell][countNumber] == 0)
			countNumber += 1;

		fprintf(outputFile, "\t- Deleted note(s) %d", countNumber+1);

		for (int j = 1; j < howManyNumber; j++)
		{
			countNumber += 1;

			while (noteRemoved[countCell][countNumber] == 0)
				countNumber += 1;

			fprintf(outputFile, ", %d", countNumber+1);
		}

		fprintf(outputFile, " at coordinates (%d,%d)\n", coordsNoteRemoved[countCell][0], coordsNoteRemoved[countCell][1]);
		countCell += 1;
		countNumber = 0;
	}
	fprintf(outputFile, "\n");
}

bool kUpletsSolve(T_Grid grid, const int k, FILE* outputFile) {

	bool hasChanged = false;

	int howManyT = 0;
	int howManyZ = 0;

	int stop = 0;
	int stopbis = 0;

	int size = getGridSize(grid);

	int* variable = malloc(sizeof(int) * k);
	int** coordsTuple = malloc(sizeof(int*) * k);

	for (int i = 0; i < k; i++)
		coordsTuple[i] = malloc(sizeof(int) * 2);

	unsigned char** noteRemoved = malloc(sizeof(unsigned char*) * size);
	int** cooNoteRemoved = malloc(sizeof(int*) * size);

	for (int i = 0; i < size; i++)
	{
		cooNoteRemoved[i] = malloc(sizeof(int) * 2);
		noteRemoved[i] = malloc(sizeof(unsigned char) * size);
	}

	unsigned char* batonHidden = malloc(size * sizeof(unsigned char));
	int* batonNaked = malloc(size * sizeof(int));

	int nbTuples = coeffBinomial(k, size);

	int** tuples = generateKTuples(k, nbTuples);

	while (stop < nbTuples && !hasChanged)
	{
		int xSquare = 0;
		int ySquare = 0;
		int sqrtS = getGridSqrtSize(grid);

		for (int i = 0; i < k; i++)
			variable[i] = tuples[stop][i];

		while (stopbis < size && hasChanged == false)
		{
			//SQUARE

			createBaton(grid, batonHidden);
			initBaton(grid, batonNaked, xSquare, xSquare + sqrtS - 1, ySquare, ySquare + sqrtS - 1);

			for (int i = 0; i < size; i++)
				createBaton(grid, noteRemoved[i]);
			initCoordinate(size, cooNoteRemoved);

			checkRectKUpletSolve(grid, batonHidden, batonNaked, xSquare, xSquare + sqrtS, ySquare, ySquare + sqrtS, k, variable);

			howManyT = howManyTrue(size, batonHidden);
			howManyZ = howManyZero(grid, batonNaked);

			if (howManyT == k)
			{
				findCooTupleSquareHidden(sqrtS, batonHidden, coordsTuple, xSquare, ySquare);
				hasChanged |= removeNoteOnCell(grid, coordsTuple, variable, k, noteRemoved, cooNoteRemoved);

				if (hasChanged)
					writeInDoc(coordsTuple, variable, outputFile, "hidden", "square", k, noteRemoved, cooNoteRemoved);
			}
			if (howManyZ == k && !hasChanged)
			{
				findCooTupleSquareNaked(sqrtS, batonNaked, coordsTuple, xSquare, ySquare);
				hasChanged |= removeNotesKUpletSquare(grid, coordsTuple, variable, k, xSquare, ySquare, noteRemoved, cooNoteRemoved);

				if (hasChanged)
					writeInDoc(coordsTuple, variable, outputFile, "naked", "square", k, noteRemoved, cooNoteRemoved);
			}

			nextSquare(getGridSqrtSize(grid), &xSquare, &ySquare);

			// LIGNE

			if (!hasChanged)
			{
				createBaton(grid, batonHidden);
				initBaton(grid, batonNaked, stopbis, stopbis, 0, size - 1);

				for (int i = 0; i < size; i++)
					createBaton(grid, noteRemoved[i]);
				initCoordinate(size, cooNoteRemoved);

				checkRectKUpletSolve(grid, batonHidden, batonNaked, stopbis, stopbis + 1, 0, size, k, variable);

				howManyT = howManyTrue(size, batonHidden);
				howManyZ = howManyZero(grid, batonNaked);

				if (howManyT == k)
				{
					findCooTupleLineHidden(size, batonHidden, coordsTuple, stopbis);
					hasChanged |= removeNoteOnCell(grid, coordsTuple, variable, k, noteRemoved, cooNoteRemoved);

					if (hasChanged)
						writeInDoc(coordsTuple, variable, outputFile, "hidden", "line", k, noteRemoved, cooNoteRemoved);
				}
				if (howManyZ == k && !hasChanged)
				{
					findCooTupleLineNaked(size, batonNaked, coordsTuple, stopbis);
					hasChanged |= removeNotesKUpletRows(grid, coordsTuple, variable, k, stopbis, noteRemoved, cooNoteRemoved);

					if (hasChanged)
						writeInDoc(coordsTuple, variable, outputFile, "naked", "line", k, noteRemoved, cooNoteRemoved);
				}
				howManyT = 0;
			}

			//COLONNE

			if (!hasChanged)
			{
				createBaton(grid, batonHidden);
				initBaton(grid, batonNaked, 0, size - 1, stopbis, stopbis);

				for (int i = 0; i < size; i++)
					createBaton(grid, noteRemoved[i]);
				initCoordinate(size, cooNoteRemoved);

				checkRectKUpletSolve(grid, batonHidden, batonNaked, 0, size, stopbis, stopbis + 1, k, variable);

				howManyT = howManyTrue(size, batonHidden);
				howManyZ = howManyZero(grid, batonNaked);

				if (howManyT == k)
				{
					findCooTupleColumnHidden(size, batonHidden, coordsTuple, stopbis);
					hasChanged |= removeNoteOnCell(grid, coordsTuple, variable, k, noteRemoved, cooNoteRemoved);

					if (hasChanged)
						writeInDoc(coordsTuple, variable, outputFile, "hidden", "colonne", k, noteRemoved, cooNoteRemoved);
				}
				if (howManyZ == k && !hasChanged)
				{
					findCooTupleColumnNaked(size, batonNaked, coordsTuple, stopbis);
					hasChanged |= removeNotesKUpletColumns(grid, coordsTuple, variable, k, stopbis, noteRemoved, cooNoteRemoved);

					if (hasChanged)
						writeInDoc(coordsTuple, variable, outputFile, "naked", "colonne", k, noteRemoved, cooNoteRemoved);
				}
			}

			stopbis++;
		}

		stopbis = 0;
		stop += 1;
	}

	free(variable);
	free(coordsTuple);
	//TODO mauvais free coordsTuple
	free(batonHidden);
	free(batonNaked);
	freeTuples(tuples, nbTuples);

	return hasChanged;
}