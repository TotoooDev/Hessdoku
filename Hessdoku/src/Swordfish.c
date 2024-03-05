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

bool doesRowBelongToSwordFish(T_ColumnFoundIndexes* item, int value) {
	return valueExistsArrayList(item->columnIndexes, value);
}


/* ************************************************
 *                 Columns Tab                    *
 ************************************************ */

typedef T_ArrayList T_ColumnTab;

void printColumnTab(T_ColumnTab tab) {
	for (int i = 0; i < tab.len; i++) {
		printColumnFoundIndexes(tab.list[i]);
	}
	printf("\n");
}


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

	freeColumnFoundIndexes(col);
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

			if (!res) {
				freeColumnTab(tempTab);
				return false;
			}

			if (count <= k) {
				addColumnToColumnTab(tempTab, i, lineIndex);
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


// TODO: logs into outputFile
bool logAndRemoveSwordfishNotes(T_Grid grid, T_ColumnTab columnTab, int noteValue, FILE* outputFile)
{
	fprintf(outputFile, "\nFound a %d-swordfish at ", columnTab.maxLen);
	for (int i = 0; i < columnTab.maxLen; i++)
	{
		for (int j = 0; j < ((T_ColumnFoundIndexes*)(columnTab.list[i]))->columnIndexes.len; j++)
		{
			fprintf(outputFile, "(%d %d) ", ((T_ColumnFoundIndexes*)(columnTab.list[i]))->columnIndexes.list[j], ((T_ColumnFoundIndexes*)(columnTab.list[i]))->column);
		}
	}
	fprintf(outputFile, "\n");

	bool hasGridChanged = false;

	for (int columnTabIndex = 0; columnTabIndex < columnTab.len; columnTabIndex++)
	{
		for (int rowIndex = 0; rowIndex < getGridSize(grid); rowIndex++)
		{
			if (!doesRowBelongToSwordFish(columnTab.list[columnTabIndex], rowIndex))
			{
				if (unsetNoteCell(getCell(grid, rowIndex, ((T_ColumnFoundIndexes*)(columnTab.list[columnTabIndex]))->column), noteValue))
				{
					hasGridChanged = true;
					fprintf(outputFile, "Deleted a %d-swordfish note in (%d %d)\n", columnTab.maxLen, rowIndex, ((T_ColumnFoundIndexes*)(columnTab.list[columnTabIndex]))->column);
				}
			}
		}
	}
	fprintf(outputFile, "\n");


	return hasGridChanged;
}

bool solveSwordfish(T_Grid grid, int k, FILE* outputFile) 
{
	for (int value = 1; value <= getGridSize(grid); value++)
	{
		T_ColumnTab columnTab = initColumnTab(k);

		int satisfactoryLinesCount = 0;

		for (int lineIndex = 0; lineIndex < getGridSize(grid); lineIndex++)
		{
			// TODO: Le cas des swordfish si on en a deux à la meme valeur dans une seule grille
			bool lineResult = searchLine(grid, value, lineIndex, k, &columnTab);

			if (lineResult)
				satisfactoryLinesCount++;
		}

		// A swordfish has been detected
		if (satisfactoryLinesCount == k) {
			bool haveNotesBeenRemoved = logAndRemoveSwordfishNotes(grid, columnTab, value, outputFile);
			
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