#include <Cell.h>

T_Cell createCell(unsigned char value) {
	bool* tab = malloc(9 * sizeof(bool));
	for (int i = 0; i < 9; i++)
	{
		tab[i] = false;
	}


	T_Cell cell;
	cell.value = value;
	cell.notes = tab;

	return cell;
}