#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
	void** list;
	int len;
	int maxLen;
} T_ArrayList;

T_ArrayList initArrayList(int maxLen, int sizeElt);
T_ArrayList copyArrayList(T_ArrayList tab, int sizeElt);
void dumpArrayList(T_ArrayList source, T_ArrayList* dest);
bool canAddValueArrayList(T_ArrayList tab, void* newVal);
bool valueExistsArrayList(T_ArrayList tab, void* col);
bool addValueArrayList(T_ArrayList* tab, void* newVal);
void freeArrayList(T_ArrayList tab);


#endif
