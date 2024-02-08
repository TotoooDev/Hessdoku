#include "Grid.h";
#include "Cell.h";

#include "Solver.h";
#include "Tests.h";



void removeAllNotes(T_Grid grid) {
	for (int i = 0; i < getGridSize(grid); i++)
	{
		for (int j = 0; j < getGridSize(grid); j++)
		{
			for (int n = 0; n < getGridSize(grid); n++)
			{
				unsetNoteCell(getCell(grid, i, j), n);
			}
		}

	}
}

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

	kUpletsSolve(testGrid, 1, NULL);
	kUpletsSolve(testGrid, 2, NULL);
	kUpletsSolve(testGrid, 3, NULL);

	return areGridEqual(testGrid, goodGrid);
}

/*
Naked K-Tuples tests
*/
bool testNaked2TupleGrid()
{
	return 0;
}

bool testNaked3TupleGrid()
{
	return 0;
}

bool testNakedLinesGrid()
{
	return 0;
}

bool testNakedColumnGrid()
{
	return 0;
}

bool testNakedZoneGrid()
{
	return 0;
}


/*
Hidden K-Tuples tests
*/
bool testNaked1TupleGrid()
{
	T_Grid testGrid = generateGrid(9, 3);
	T_Grid goodGrid = generateGrid(9, 3);

	removeAllNotes(testGrid);
	removeAllNotes(goodGrid);

	setNoteCell(getCell(testGrid, 0, 0), 5);
	setNoteCell(getCell(testGrid, 0, 0), 6);
	setNoteCell(getCell(testGrid, 0, 0), 8);
	setNoteCell(getCell(testGrid, 0, 0), 7); // TODO

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

bool testHiddenLinesGrid()
{
	return 0;
}

bool testHiddenColumnGrid()
{
	return 0;
}

bool testHiddenZoneGrid()
{
	return 0;
}



int mainTestNaked()
{
	T_Test* test = initTest();


	addTest(test, &testAllNotesGrid, "Test fonctionnel : Grille sans notes");
	addTest(test, &testNormalGridWithout23Tuples, "Test fonctionnel : Grille sans 2 - 3 uplets");

	testNextStep(test);
	testNextStep(test);

	concludeTests(test);

	return EXIT_SUCCESS;
}