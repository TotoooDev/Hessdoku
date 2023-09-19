#include <Cell.h>
#include <Log.h>

// TODO: test this !!!
T_Cell *createCell(unsigned char value) {
	// As the number of bits can only be specified in the struct, this function prints a warning if the size of value is too big
	if (value > 9) {
		LOG("An error has occured : a cell's value must be smaller than 10. Value provided : %c", value);
	}

	// Creating the array of notes
	bool* tab = malloc(9 * sizeof (bool));
	for (int i = 0; i < 9; i++)
	{
		tab[i] = false;			// FIXME : handle the NULL case (assertion ?)
	}

	// Allocating the new cell
	T_Cell* newCell = malloc(sizeof (T_Cell));
	newCell->value = value;		// FIXME : handle the NULL case (assertion ?)
	newCell->notes = tab;		// FIXME : handle the NULL case (assertion ?)

	return newCell;
}

// TODO: test this function
void freeCell(T_Cell *cell) {
	free(cell->notes);
	free(cell);
}