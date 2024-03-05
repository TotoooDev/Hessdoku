#include "ArrayList.h"

T_ArrayList initArrayList(int maxLen, int sizeElt)
{
	T_ArrayList arrayList;

	void** tab = (void**)malloc(sizeof(void*) * maxLen);
	assert(tab != NULL);

	for (int i = 0; i < maxLen; i++)
	{
		tab[i] = NULL;
	}

	arrayList.len = 0;
	arrayList.list = tab;
	arrayList.maxLen = maxLen;

	return arrayList;
}

T_ArrayList copyArrayList(T_ArrayList tab, int sizeElt)
{
	T_ArrayList newList;

	newList.len = tab.len;
	newList.maxLen = tab.maxLen;

	newList.list = (void**)malloc(sizeof(void*) * newList.maxLen);
	assert(newList.list != NULL);


	for (int i = 0; i < newList.maxLen; i++)
		newList.list[i] = tab.list[i];

	return newList;
}

void dumpArrayList(T_ArrayList source, T_ArrayList* dest)
{
	free(dest->list);
	dest->list = source.list;
	dest->maxLen = source.maxLen;
	dest->len = source.len;
}


bool canAddValueArrayList(T_ArrayList list, void* newVal)
{
	for (int i = 0; i < list.maxLen; i++)
	{
		if (list.list[i] == NULL || list.list[i] == newVal)
			return true;
	}
	return false;
}

bool valueExistsArrayList(T_ArrayList tab, void* col)
{
	for (int i = 0; i < tab.maxLen; i++)
	{
		if (tab.list[i] == col)
			return true;
	}
	return false;
}

bool addValueArrayList(T_ArrayList* tab, void* newVal)
{
	for (int i = 0; i < tab->maxLen; i++)
	{
		if (tab->list[i] == newVal)
			return true;

		if (tab->list[i] == NULL)
		{
			tab->list[i] = newVal;
			tab->len++;

			return true;
		}
	}
	return false;
}

void freeArrayList(T_ArrayList list) {
	free(list.list);
}
