#include "Swordfish.h"


/* Structuure that stores the useful data to find valid numbers */
typedef struct {
	int* tab;
	int len;
	int k;
} T_ColumnTab;


T_ColumnTab initColumnTab(int k) 
{
	T_ColumnTab columnsTab;

	int* tab = (int*)malloc(sizeof(int) * k);
	assert(tab != NULL);

	for (int i = 0; i < k; i++) 
	{
		tab[i] = 0;
	}

	columnsTab.len = 0;
	columnsTab.tab = tab;
	columnsTab.k = k;

	return columnsTab;
}

T_ColumnTab copyColumnTab(T_ColumnTab tab) 
{
	T_ColumnTab newTab;

	newTab.len = tab.len;
	newTab.k = tab.k;

	newTab.tab = (int*)malloc(sizeof(int) * newTab.k);
	assert(newTab.tab != NULL);


	for (int i = 0; i < newTab.k; i++)
		newTab.tab[i] = tab.tab[i];

	return newTab;
}

void dumpColumnTab(T_ColumnTab source, T_ColumnTab* dest)
{
	free(dest->tab);
	dest->tab = source.tab;
	dest->k = source.k;
	dest->len = source.len;
}


bool canAddValueColumnTab(T_ColumnTab tab, int newVal) 
{
	for (int i = 0; i < tab.k; i++) 
	{
		if (tab.tab[i] == 0 || tab.tab[i] == newVal)
			return true;
	}
	return false;
}

bool valueExistsColumnTab(T_ColumnTab tab, int col) 
{
	for (int i = 0; i < tab.k; i++) 
	{
		if (tab.tab[i] == col)
			return true;
	}
	return false;
}

bool addValueColumnTab(T_ColumnTab* tab, int newVal) 
{
	for (int i = 0; i < tab->k; i++) 
	{
		if (tab->tab[i] == newVal)
			return true;

		if (tab->tab[i] == 0)
		{
			tab->tab[i] = newVal;
			tab->len++;

			return true;
		}
	}
	return false;
}





/* columnsNoteIndexTab */
typedef struct 
{
	int** tab;
	int len;
	int k;
} T_ColumnNoteIndexTab;

init();
addToColumn(T_ColumnNoteIndexTab tab, int colIndex, int value) {

}





bool searchLine(T_Grid grid, int value, int lineIndex, int k, T_ColumnTab* columnTab, int** columnsNoteIndexTab)
{
	int count = 0;
	T_ColumnTab tempTab = copyColumnTab(*columnTab);

	for (int i = 0; i < lineIndex; i++)  
	{
		if (isNoteInCell(getCell(grid, lineIndex, i), value))
		{
			int res = addValueColumnTab(&tempTab, i);

			if (!res) {
				return false;
			}

			count++;
		}
	}

	if (count < k && count >= 2)
	{
		dumpColumnTab(tempTab, columnTab);
	}
}

bool solveSwordfish(T_Grid grid, int k, FILE* outputFile) 
{
	T_ColumnTab columnTab = initColumnTab(k);

	//int** columnsNoteIndexTab = (int**)malloc(sizeof(int*) * k);
	//assert(columnsNoteIndexTab != NULL);

	/*for (int i = 0; i < k; i++) 
	{
		columnsNoteIndexTab[i] = (int*)malloc(sizeof(int) * k);
		assert(columnsNoteIndexTab[i] != NULL);
	}*/

	addValueColumnTab(&columnTab, 5);
	addValueColumnTab(&columnTab, 5);
	addValueColumnTab(&columnTab, 4);

	T_ColumnTab newColumnTab = copyColumnTab(columnTab);

	addValueColumnTab(&columnTab, 2);

	for (int i = 0; i < columnTab.k; i++) {
		printf("%d ", columnTab.tab[i]);
	}
	printf("\n");

	for (int i = 0; i < newColumnTab.k; i++) {
		printf("%d ", newColumnTab.tab[i]);
	}
	printf("\n");
}
