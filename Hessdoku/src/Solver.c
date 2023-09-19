#include <Solver.h>


void resetWitness(bool * w)
{
	for (int i = 0; i < 9; i++)
	{
		w[i] = false;
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
					if (grid[x][y]->value != 0)
					{
						if (witness[(grid[x + nextX][y + nextY]->value) - 1] == true)
						{
							return false;
						}
						else
						{
							witness[(grid[x][y]->value) - 1] = true;
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
}