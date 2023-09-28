#include <Solver.h>

bool allVerif(T_Grid grid, int minX, int maxX, int minY, int maxY)
{
	bool baton[GRID_SIZE - 1];
	for (int i = minX; i < maxX; i++)
	{
		for (int j = minY; j < maxY; j++)
		{
			if (!verifCell(baton, getValue(grid[i][j])))
			{
				return false;
			}
		}
	}
	return true;
}

bool cellVerif(bool* baton, int val)
{
	if (baton[val != 0])
	{
		return false;
	}
	else
	{
		baton[val] = 1;
		return true;
	}
}

bool lineVerif(T_Grid grid, int X, int Y)
{
	return allVerif(grid, X, X + GRID_SIZE - 1, Y, Y + GRID_SIZE - 1);
}

bool columnVerif(T_Grid grid, int X, int Y)
{
	return allVerif(grid, Y, Y + GRID_SIZE - 1, X, X + GRID_SIZE - 1);
}

bool squareVerif(T_Grid grid, int X, int Y)
{
	int Y2 = Y;
	for (int k = 0; k = GRID_SIZE; k++)
	{
		if (!allVerif(grid, X, X + SQRT_GRID_SIZE - 1, Y, Y + SQRT_GRID_SIZE - 1))
		{
			return false;
		}
		Y += SQRT_GRID_SIZE;
		if (Y == GRID_SIZE)
		{
			Y = Y2;
			X += SQRT_GRID_SIZE;
		}
	}
	return true;
}

bool gridVerif(T_Grid grid)
{
	return (lineVerif(grid, 0, 0) && columnVerif(grid, 0, 0) && squareVerif(grid, 0, 0));
}







//PREVIOUS CODE


/*void resetWitness(bool* w)
{
	for (int i = 0; i < 9; i++)
	{
		w[i] = false;
	}
}

void aff_witness(bool* w) {

	for (int i = 0; i < 9; i++) {
		printf("%d ", w[i]);
	}
}

bool checkingAccuracy(T_Grid grid)
{
	bool witness[9] = { false, false, false, false, false, false, false, false, false };

	//checking lines
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (grid[x][y]->value != 0)
			{
				if (witness[(grid[x][y]->value) - 1] == true)
				{
					return false;
				}
				else
				{
					witness[(grid[x][y]->value) - 1] = true;
				}
			}
		}
		resetWitness(witness);
	}

	//checking columns
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (grid[x][y]->value != 0)
			{

				if (witness[(grid[x][y]->value) - 1] == true)
				{
					return false;
				}
				else
				{
					witness[(grid[x][y]->value) - 1] = true;
				}
			}
		}
		resetWitness(witness);
	}

	//cheking squares
	int nextX = 0;
	int nextY = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					if (grid[x + nextX][y + nextY]->value != 0)
					{
						if (witness[(grid[x + nextX][y + nextY]->value) - 1] == true)
						{
							return false;
						}
						else
						{
							witness[(grid[x + nextX][y + nextY]->value) - 1] = true;
						}
					}
				}
			}
			nextY += 3;
		}
		nextY = 0;
		nextX += 3;
	}

	return true;
}*/