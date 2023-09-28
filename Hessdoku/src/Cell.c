#include <Cell.h>
#include <Log.h>

// TODO: test this !!!
T_Cell *createCell(unsigned char value) {
	// As the number of bits can only be specified in the struct, this function prints a warning if the size of value is too big
	if (value > 9) {
		LOG("An error has occured : a cell's value must be smaller than 10. Value provided : %c", value);
	}

	// Allocating the new cell
	T_Cell* newCell = malloc(sizeof (T_Cell));
	newCell->notes = value;		// FIXME : handle the NULL case (assertion ?)

	return newCell;
}

// TODO: test this function
void freeCell(T_Cell *cell) {
	free(cell);
}