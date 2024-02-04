#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>;
#include <stdio.h>;
#include <stdlib.h>;


typedef struct T_TestDataStruct 
{
	bool (*testedFunction)();		// Pointer to a test function
	char* msg;
} T_TestData;

typedef struct T_TestQueueStruct
{
	T_TestData* data;
	struct T_TestQueueStruct* nextTest;
} T_TestQueue;


/**
* Test struct : contains all the data for the tests
* @param queue: the queue that contains all the tests to be done
* @param skippedAmount: the amount of tests that have been skipped
* @param successAmount: the amount of tests that have succeed
* @param failedAmount: the amount of tests that have failed
*/
typedef struct T_TestStruct {
	T_TestQueue* queue;
	int skippedAmount;
	int successAmount;
	int failedAmount;
} T_Test;



/**
* Initializes and returns a test struct, that will contain the tests data and results
* @returns the test struct that contains all the test data
*/
T_Test* initTest();

/**
* Adds a test to be computed to the tests queue.
* @param test: the test struct that contains all the test data
* @param testedFunction: the function to be added to the stack
* @param msg: the test description
*/
void addTest(T_Test* test, bool (*testedFunction)(), char* msg);

/**
* Computes the next test in the queue, and displays its result
* @param test: the test struct that contains all the test data
*/
void testNextStep(T_Test* test);

/**
* Skips a test in the queue.
* @param test: the test struct that contains all the test data
*/
void skipTest(T_Test* test);

/**
* Displays the tests results.
* @param test: the test struct that contains all the test data
*/
void concludeTests(T_Test* test);



//void testAssert(bool predicate, char* msg);

// void testAssertGrid(T_Grid grid, char* msg);

#endif