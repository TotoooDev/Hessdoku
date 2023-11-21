#include <Solver.h>

void createBaton(unsigned char* b)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		b[i] = 0;
	}
}

bool allVerif(T_Grid grid, int minX, int maxX, int minY, int maxY, unsigned char * baton)
{
	for (int i = minX; i < maxX; i++)
	{
		for (int j = minY; j < maxY; j++)
		{
			
			if (!cellVerif(baton, getValue(grid, i, j)))
			{
				return false;
			}
		}
	}
	return true;
}

bool cellVerif(unsigned char * baton, int val)
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

bool lineVerif(T_Grid grid)
{
	unsigned char* baton = malloc(GRID_SIZE * sizeof(unsigned char));
	createBaton(baton);
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (!allVerif(grid, i, i+1, 0, GRID_SIZE, baton))
		{
			return false;
		}
		createBaton(baton);
	}
	return true;
}

bool columnVerif(T_Grid grid)
{
	unsigned char* baton = malloc(GRID_SIZE * sizeof(unsigned char));
	createBaton(baton);
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (!allVerif(grid, 0, GRID_SIZE, i, i+1, baton))
		{
			return false;
		}
		createBaton(baton);
	}
	return true;
}

bool squareVerif(T_Grid grid)
{
	unsigned char* baton = malloc(GRID_SIZE * sizeof(unsigned char));
	createBaton(baton);
	int X = 0;
	int Y = 0;
	for (int k = 0; k < GRID_SIZE; k++)
	{
		if (!allVerif(grid, X, X + SQRT_GRID_SIZE, Y, Y + SQRT_GRID_SIZE, baton))
		{
			return false;
		}
		Y += SQRT_GRID_SIZE;
		if (Y == GRID_SIZE)
		{
			Y = 0;
			X += SQRT_GRID_SIZE;
		}
		if (X == GRID_SIZE)
		{
			X = 0;
		}
		createBaton(baton);
	}
	return true;
}

bool gridVerif(T_Grid grid)
{
	return (lineVerif(grid) && columnVerif(grid) && squareVerif(grid));
}

bool removeNotesInGridByRows(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	for (int k = 0; k < GRID_SIZE; k++)						// Checking for lines
	{
		tempCell = grid[x][k];
		if (tempCell == currentCell) continue;

		hasChanged |= unsetNoteCell(tempCell, currentValue);
	}

	return hasChanged;
}

bool removeNotesInGridByColumns(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		tempCell = grid[i][y];
		if (tempCell == currentCell) continue;

		hasChanged |= unsetNoteCell(tempCell, currentValue);
	}

	return hasChanged;
}

bool removeNotesInGridByBlocks(T_Grid grid, T_Cell* currentCell, unsigned int currentValue, int x, int y)
{
	bool hasChanged = false;
	T_Cell* tempCell;

	int boxRow = x / SQRT_GRID_SIZE * SQRT_GRID_SIZE;
	int boxCol = y / SQRT_GRID_SIZE * SQRT_GRID_SIZE;
	for (int m = 0; m < SQRT_GRID_SIZE; m++)
	{
		for (int n = 0; n < SQRT_GRID_SIZE; n++)
		{
			tempCell = grid[boxRow + m][boxCol + n];
			if (tempCell == currentCell) continue;

			hasChanged |= unsetNoteCell(tempCell, currentValue);
		}
	}

	return hasChanged;
}

bool removeNotesInGridByZones(T_Grid grid)
{
	bool hasChanged = false;

	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++) 
		{
			T_Cell* currentCell = grid[x][y];
			unsigned int currentValue = getValueOfCell(currentCell);
			
			if (currentValue == 0) continue;
			
			hasChanged |= removeNotesInGridByColumns(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByRows(grid, currentCell, currentValue, x, y);

			hasChanged |= removeNotesInGridByBlocks(grid, currentCell, currentValue, x, y);

		}
	}
	return hasChanged;
}
