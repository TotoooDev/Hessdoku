#include "Tests.h"
#include <string.h>

#define SUCCESS_MESSAGE "OK : le test %s a ete passe avec succes.\n"
#define ERROR_MESSAGE "KO : le test %s a echoue \n"



/* *********************************
	Test data functions
  ********************************* */

T_TestData* createTestData(bool (*testedFunction)(), char* msg)
{
	T_TestData* data = malloc(sizeof(T_TestData));

	data->testedFunction = testedFunction;
	data->msg = msg;

	return data;
}

bool runTestData(T_TestData* data, char* msg) 
{
	strcpy(msg, data->msg);

	return (*data->testedFunction)();
}

void freeData(T_TestData* data) 
{
	free(data);
}



/* *********************************
	Queue functions 
  ********************************* */

T_TestData* getTest(T_TestQueue* queue)
{
	return queue->data;
}
	
T_TestQueue* getNextQueueElement(T_TestQueue* queue)
{
	return queue->nextTest;
}

T_TestQueue* createQueue(T_TestData* data)
{
	T_TestQueue* queue = malloc(sizeof(T_TestQueue));
	
	queue->nextTest = NULL;
	queue->data = data;

	return queue;
}

T_TestQueue* addNextQueue(T_TestQueue* queue, T_TestData* data)
{
	if (queue == NULL)
		return createQueue(data);

	else
	{
		T_TestQueue* tempQueue = queue;

		while (tempQueue->nextTest != NULL) {
			tempQueue = tempQueue->nextTest;
		}

		tempQueue->nextTest = createQueue(data);
		tempQueue->nextTest->data = data;

		return queue;
	}
}

void freeQueue(T_TestQueue* queue)
{
	freeData(queue->data);
	free(queue);
}

T_TestQueue* removeQueueElt(T_TestQueue* queue)
{
	T_TestQueue* newQueue = queue->nextTest;

	freeQueue(queue);

	return newQueue;
}


/* *********************************
	Test functions
  ********************************* */

T_Test* initTest()
{
	T_Test* test = malloc(sizeof(T_Test));

	test->queue = NULL;
	test->failedAmount = 0;
	test->successAmount = 0;
	test->skippedAmount = 0;

	printf("         Initialisation des tests reussie !           \n\n");

	printf("######################################################\n");
	printf("#              Projet sudoku : Tests                 #\n");
	printf("######################################################\n\n");

	return test;
}

void addTest(T_Test* test, bool (*testedFunction)(), char* msg)
{
	T_TestData* data = createTestData(testedFunction, msg);
	test->queue = addNextQueue(test->queue, data);
}

void testNextStep(T_Test* test) 
{
	char msg[1000];

	bool success = runTestData(getTest(test->queue), msg);
	
	test->queue = removeQueueElt(test->queue);

	if (success)
	{
		test->successAmount++;
		printf(SUCCESS_MESSAGE, msg);
	}
	else
	{
		test->failedAmount++;
		printf(ERROR_MESSAGE, msg);
	}
}

void skipTest(T_Test* test)
{
	test->queue = removeQueueElt(test->queue);

	test->skippedAmount++;
}

void concludeTests(T_Test* test)
{
	printf("\nBilan des tests :\n");
	printf("  - Tests reussis : %d\n", test->successAmount);
	printf("  - Tests echoues : %d\n", test->failedAmount);
	printf("  - Tests evites : %d\n\n", test->skippedAmount);

	printf("######################################################\n");
	printf("#                  Fin des tests                     #\n");
	printf("######################################################\n\n");
}