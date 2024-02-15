#include "Grid.h"
#include "Cell.h"

#include "Solver.h"
#include "Tests.h"


/*
Utilitary functions
*/

void removeAllNotes(T_Grid grid) {
	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int j = 0; j < getGridSize(grid); j++)
		{
			for (int n = 1; n < getGridSize(grid) + 1; n++)
			{
				unsetNoteCell(getCell(grid, i, j), n);
			}
		}

	}
}

void addNotesToGrid(T_Grid* grid, int x, int y, int notes[], int nbNotes)
{
	for (int i = 0; i < nbNotes; i++)
	{
		setNoteCell(getCell(*grid, x, y), notes[i]);
	}
}

void removeNotesOnGrid(T_Grid* grid, int x, int y, int notes[], int nbNotes)
{
	for (int i = 0; i < nbNotes; i++)
	{
		unsetNoteCell(getCell(*grid, x, y), notes[i]);
	}
}

void removeNotesOnZoneLineAndColumn(T_Grid* grid, int value) 
{
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (!(i == 0 && j == 0))
			{
				unsetNoteCell(getCell(*grid, i, j), value);
				unsetNoteCell(getCell(*grid, i, j), value);
			}
		}
	}

	for (int i = 3; i < 9; i++)
	{
		unsetNoteCell(getCell(*grid, i, 0), value);
		unsetNoteCell(getCell(*grid, 0, i), value);
	}
}

void removeNotesOnZone(T_Grid* grid, int startX, int endX, int startY, int endY, int value) 
{
	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			unsetNoteCell(getCell(*grid, x, y), value);
		}
	}
}



/*
Functionnal tests
*/


/*
General tests
*/


bool testAllNotesGrid()
{
	T_Grid testGrid = generateGrid(9, 3);

	T_Grid goodGrid = generateGrid(9, 3);

	kUpletsSolve(testGrid, 1, NULL);
	kUpletsSolve(testGrid, 2, NULL);
	kUpletsSolve(testGrid, 3, NULL);

	return areGridEqual(testGrid, goodGrid);
}

bool testNormalGridWithout23Tuples() {
	T_Grid testGrid = generateGrid(9, 3);

	T_Grid goodGrid = generateGrid(9, 3);

	unsetNoteCell(getCell(testGrid, 0, 0), 5);
	unsetNoteCell(getCell(testGrid, 0, 0), 6);
	unsetNoteCell(getCell(testGrid, 0, 0), 7);
	unsetNoteCell(getCell(testGrid, 0, 0), 8);
	unsetNoteCell(getCell(testGrid, 0, 1), 9);
	unsetNoteCell(getCell(testGrid, 0, 0), 5);

	unsetNoteCell(getCell(goodGrid, 0, 0), 5);
	unsetNoteCell(getCell(goodGrid, 0, 0), 6);
	unsetNoteCell(getCell(goodGrid, 0, 0), 7);
	unsetNoteCell(getCell(goodGrid, 0, 0), 8);
	unsetNoteCell(getCell(goodGrid, 0, 1), 9);
	unsetNoteCell(getCell(goodGrid, 0, 0), 5);

	kUpletsSolve(testGrid, 1, stderr);
	kUpletsSolve(testGrid, 2, stderr);
	kUpletsSolve(testGrid, 3, stderr);

	return areGridEqual(testGrid, goodGrid);
}

/*
Naked K-Tuples tests
*/
bool testNaked1TupleGrid()
{
	T_Grid testGrid = generateGrid(9, 3);
	T_Grid goodGrid = generateGrid(9, 3);

	// Adding values to the test grid
	int gridNotesToRemoveSingleton[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

	removeNotesOnGrid(&testGrid, 0, 0, gridNotesToRemoveSingleton, 8);

	// Adding values to the valid grid 
	removeNotesOnGrid(&goodGrid, 0, 0, gridNotesToRemoveSingleton, 8);

	removeNotesOnZoneLineAndColumn(&goodGrid, 1);

	// Running the function
	FILE* null = fopen("nul", "w");

	kUpletsSolve(testGrid, 1, null); // Test on columns
	kUpletsSolve(testGrid, 1, null); // Test on lines
	kUpletsSolve(testGrid, 1, null); // Test on zones

	return areGridEqual(testGrid, goodGrid);
}

bool testNaked2TupleGrid()
{
	T_Grid testGrid = generateGrid(9, 3);
	T_Grid goodGrid = generateGrid(9, 3);

	// Adding values to the test grid
	int gridNotesToRemoveSingleton[7] = { 3, 4, 5, 6, 7, 8, 9 };

	removeNotesOnGrid(&testGrid, 0, 0, gridNotesToRemoveSingleton, 7);
	removeNotesOnGrid(&testGrid, 0, 1, gridNotesToRemoveSingleton, 7);

	// Adding values to the valid grid 
	removeNotesOnGrid(&goodGrid, 0, 0, gridNotesToRemoveSingleton, 7);
	removeNotesOnGrid(&goodGrid, 0, 1, gridNotesToRemoveSingleton, 7);

	// Removing notes in the square zone
	removeNotesOnZone(&goodGrid, 1, 2, 0, 2, 1);
	removeNotesOnZone(&goodGrid, 1, 2, 0, 2, 2);

	// Removing notes in the line
	removeNotesOnZone(&goodGrid, 0, 0, 2, 8, 1);
	removeNotesOnZone(&goodGrid, 0, 0, 2, 8, 2);

	// Running the function
	FILE* null = fopen("nul", "w");

	kUpletsSolve(testGrid, 2, null); // Test on columns
	kUpletsSolve(testGrid, 2, null); // Test on lines
	kUpletsSolve(testGrid, 2, null); // Test on columns (no changes expected)

	return areGridEqual(testGrid, goodGrid);
}

bool testNaked3TupleGrid()
{
	T_Grid testGrid = generateGrid(9, 3);
	T_Grid goodGrid = generateGrid(9, 3);

	// Adding values to the test grid
	int gridNotesToRemoveSingleton[6] = { 4, 5, 6, 7, 8, 9 };

	removeNotesOnGrid(&testGrid, 0, 0, gridNotesToRemoveSingleton, 6);
	removeNotesOnGrid(&testGrid, 0, 1, gridNotesToRemoveSingleton, 6);
	removeNotesOnGrid(&testGrid, 0, 2, gridNotesToRemoveSingleton, 6);

	// Adding values to the valid grid 
	removeNotesOnGrid(&goodGrid, 0, 0, gridNotesToRemoveSingleton, 6);
	removeNotesOnGrid(&goodGrid, 0, 1, gridNotesToRemoveSingleton, 6);
	removeNotesOnGrid(&goodGrid, 0, 2, gridNotesToRemoveSingleton, 6);

	// Removing notes in the square zone
	removeNotesOnZone(&goodGrid, 1, 2, 0, 2, 1);
	removeNotesOnZone(&goodGrid, 1, 2, 0, 2, 2);
	removeNotesOnZone(&goodGrid, 1, 2, 0, 2, 3);

	// Removing notes in the line
	removeNotesOnZone(&goodGrid, 0, 0, 3, 8, 1);
	removeNotesOnZone(&goodGrid, 0, 0, 3, 8, 2);
	removeNotesOnZone(&goodGrid, 0, 0, 3, 8, 3);

	// Running the function
	FILE* null = fopen("nul", "w");

	kUpletsSolve(testGrid, 3, null); // Test on lines
	kUpletsSolve(testGrid, 3, null); // Test on zones
	kUpletsSolve(testGrid, 3, null); // Test on columns (no changes expected)

	return areGridEqual(testGrid, goodGrid);
}


/*
Hidden K-Tuples tests
*/
bool testHidden1TupleGrid()
{
	return 0;
}

bool testHidden2TupleGrid()
{
	return 0;
}

bool testHidden3TupleGrid()
{
	return 0;
}



int mainTestNaked()
{
	T_Test* test = initTest();


	addTest(test, &testAllNotesGrid, "Test fonctionnel : Grille sans notes");
	addTest(test, &testNormalGridWithout23Tuples, "Test fonctionnel : Grille sans 2 - 3 uplets");

	addTest(test, &testNaked1TupleGrid, "Test fonctionnel : Grille avec un 1-uplet nu");
	addTest(test, &testNaked2TupleGrid, "Test fonctionnel : Grille avec un 2-uplet nu");
	addTest(test, &testNaked3TupleGrid, "Test fonctionnel : Grille avec un 3-uplet nu");

	testNextStep(test);
	testNextStep(test);
	testNextStep(test);
	testNextStep(test);
	testNextStep(test);

	concludeTests(test);

	return EXIT_SUCCESS;
}