#include "Swordfish.h"


/* ************************************************
 *            Found column indexes                *
 ************************************************ */

typedef struct
{
	int column;
	T_ArrayList columnIndexes;
} T_ColumnFoundIndexes;

T_ColumnFoundIndexes* initColumnFoundIndexes(int k, int column) 
{
	T_ColumnFoundIndexes* newItem = (T_ColumnFoundIndexes*)malloc(sizeof(T_ColumnFoundIndexes));

	newItem->column = column;
	newItem->columnIndexes = initArrayList(k, sizeof(int));

	for (int i = 0; i < k; i++) {
		newItem->columnIndexes.list[i] = -1;
	}

	return newItem;
}

bool addToColumnFoundIndexes(T_ColumnFoundIndexes* item, int value)
{
	T_ArrayList* tab = &(item->columnIndexes);

	for (int i = 0; i < tab->maxLen; i++)
	{
		if (tab->list[i] == value)
			return true;

		if (tab->list[i] == -1)
		{
			tab->list[i] = value;
			tab->len++;

			return true;
		}
	}
	return false;
}

T_ColumnFoundIndexes* copyColumnFoundIndexes(T_ColumnFoundIndexes* source) {
	T_ColumnFoundIndexes* destination = initColumnFoundIndexes(source->columnIndexes.maxLen, source->column);

	destination->column = source->column;
	destination->columnIndexes = copyArrayList(source->columnIndexes, sizeof(int));

	return destination;
}

T_ColumnFoundIndexes* freeColumnFoundIndexes(T_ColumnFoundIndexes* item)
{
	freeArrayList(item->columnIndexes);
	free(item);
}

void printColumnFoundIndexes(T_ColumnFoundIndexes* item) {
	printf("col : %d, indexes (%d) : [ ", item->column, item->columnIndexes.len);

	for (int i = 0; i < item->columnIndexes.len; i++)
	{
		printf("%d ", item->columnIndexes.list[i]);
	}

	printf("] ");
}


/* ************************************************
 *                 Columns Tab                    *
 ************************************************ */

typedef T_ArrayList T_ColumnTab;


T_ColumnTab initColumnTab(int k) 
{
	return initArrayList(k, sizeof(T_ColumnFoundIndexes*));
}

T_ColumnTab copyColumnTab(T_ColumnTab tab) 
{
	T_ColumnTab copy = copyArrayList(tab, sizeof(T_ColumnFoundIndexes*));

	for (int i = 0; i < copy.len; i++)
	{
		copy.list[i] = copyColumnFoundIndexes(tab.list[i]);
	}

	return copy;
}

void dumpColumnTab(T_ColumnTab source, T_ColumnTab* dest)
{
	dumpArrayList(source, dest);
}

// TODO
bool canAddValueColumnTab(T_ColumnTab tab, int column) 
{
	T_ColumnFoundIndexes* col = initColumnFoundIndexes(tab.maxLen, column);

	return canAddValueArrayList(tab, col);
}

bool valueExistsColumnTab(T_ColumnTab tab, int col) 
{
	return valueExistsArrayList(tab, col);
}

bool addValueColumnTab(T_ColumnTab* tab, int newVal) 
{
	T_ColumnFoundIndexes* col = initColumnFoundIndexes(tab->maxLen, newVal);

	for (int i = 0; i < tab->maxLen; i++)
	{
		if (tab->list[i] == NULL)
		{
			tab->list[i] = col;
			tab->len++;

			return true;
		}

		if (((T_ColumnFoundIndexes*)(tab->list[i]))->column == newVal)
			return true;
	}

	return false;
}

void freeColumnTab(T_ColumnTab tab) {
	freeArrayList(tab);
}


int getColumnIndexOnColumnTab(T_ColumnTab tab, int column) {
	int i = 0;
	while (i < tab.len && ((T_ColumnFoundIndexes*)(tab.list[i]))->column != column)
	{
		i++;
	}

	assert(i < tab.len);

	return i;
}

void printColumnTab(T_ColumnTab tab) {
	for (int i = 0; i < tab.len; i++) {
		printColumnFoundIndexes(tab.list[i]);
	}
	printf("\n");
}


/* Found column indexes integration */

void addColumnToColumnTabOnIndex(T_ColumnTab tab, int colIndex, int value) 
{
	addToColumnFoundIndexes(tab.list[colIndex], value);
}

void addColumnToColumnTab(T_ColumnTab tab, int columnNb, int value) 
{
	int i = getColumnIndexOnColumnTab(tab, columnNb);

	addToColumnFoundIndexes(tab.list[i], value);
}



/* ************************************************
 *                  Algorithm                     *
 ************************************************ */


bool searchLine(T_Grid grid, int value, int lineIndex, int k, T_ColumnTab* columnTab)
{
	int count = 0;
	T_ColumnTab tempTab = copyColumnTab(*columnTab);

	for (int i = 0; i < getGridSize(grid); i++)  
	{
		if (isNoteInCell(getCell(grid, lineIndex, i), value))
		{
			int res = addValueColumnTab(&tempTab, i);

			if (count <= k) {
				printColumnTab(tempTab);
				addColumnToColumnTab(tempTab, i, lineIndex);
			}

			if (!res) {
				freeColumnTab(tempTab);
				return false;
			}

			count++;
		}
	}

	if (count >= 2 && count <= k)
	{
		dumpColumnTab(tempTab, columnTab);
		return true;
	}

	return false;
}

bool removeSwordfishNotes(T_Grid grid, T_ColumnTab columnTab, FILE* outputFile) {
	return true;
}

bool solveSwordfish(T_Grid grid, int k, FILE* outputFile) 
{
	T_ColumnTab columnTab = initColumnTab(k);

	for (int value = 6; value <= getGridSize(grid); value++)
	{
		printf("\n\nValue : %d\n", value);

		T_ColumnTab columnTab = initColumnTab(k);
		int satisfactoryLinesCount = 0;

		for (int lineIndex = 0; lineIndex < getGridSize(grid); lineIndex++)
		{
			bool lineResult = searchLine(grid, value, lineIndex, k, &columnTab);

			if (lineResult)
				satisfactoryLinesCount++;
		}

		if (satisfactoryLinesCount == k) {
			bool haveNotesBeenRemoved = removeSwordfishNotes(grid, columnTab, outputFile);
			
			if (haveNotesBeenRemoved) {
				return true;
			}
		}
	}

	return false;
}

// TODO: Tester les fuites de mémoire



/* Bon on a des tests c cool
	addValueColumnTab(&columnTab, 5);
	addValueColumnTab(&columnTab, 5);
	addValueColumnTab(&columnTab, 4);

	T_ColumnTab newColumnTab = copyColumnTab(columnTab);

	addValueColumnTab(&columnTab, 2);

	addColumnToColumnTab(columnTab, 5, 8);
	addColumnToColumnTab(columnTab, 5, 8);
	addColumnToColumnTab(columnTab, 5, 9);
	addColumnToColumnTab(columnTab, 5, 10);
	addColumnToColumnTab(columnTab, 5, 11);

	dumpColumnTab(columnTab, &newColumnTab);

	for (int i = 0; i < columnTab.len; i++) {
		printColumnFoundIndexes(columnTab.list[i]);
	}
	printf("\n");

	for (int i = 0; i < newColumnTab.len; i++) {
		printColumnFoundIndexes(newColumnTab.list[i]);
	}
	printf("\n");
*/