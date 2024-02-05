#include <stdlib.h>
#include <stdbool.h>

#include "Tests.h"


/* *********************************
	Main
  ********************************* */


int toto(int a, int b)
{
	return a + b;
}

bool totoTest()
{
	return toto(5, 6) == 67;
}

bool totoTest2()
{
	return toto(5, 6) == 11;
}

int mainTest()
{
	T_Test* test = initTest();


	addTest(test, &totoTest, "test toto 1");
	addTest(test, &totoTest2, "test toto 2");

	testNextStep(test);
	testNextStep(test);

	concludeTests(test);

	return EXIT_SUCCESS;
}
