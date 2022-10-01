/* testDynArray.c
 * This file is used for testing the dynamicArray.c file.
 * This test suite is by no means complete or thorough.
 * More testing is needed on your own.
 */
#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"


void assertTrue(int predicate, char *message)
{
	printf("%s: ", message);
	if (predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}


// this main function contains some
int main(int argc, char* argv[]){

	DynArr *dyn;
	dyn = createDynArr(2);

	printf("\n\nTesting addDynArr...\n");
	addDynArr(dyn, 3);
	addDynArr(dyn, 4);
	addDynArr(dyn, 10);
	addDynArr(dyn, 5);
	addDynArr(dyn, 6);

	printf("The array's content: [3,4,10,5,6]\n");
	assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
	assertTrue(EQ(getDynArr(dyn, 1), 4), "Test 2nd element == 4");
	assertTrue(EQ(getDynArr(dyn, 2), 10), "Test 3rd element == 10");
	assertTrue(EQ(getDynArr(dyn, 3), 5), "Test 4th element == 5");
	assertTrue(EQ(getDynArr(dyn, 4), 6), "Test 5th element == 6");
	assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");

	printf("\n\nTesting putDynArr...\nCalling putDynArr(dyn, 2, 7)\n");
	putDynArr(dyn, 2, 7);
	printf("The array's content: [3,4,7,5,6]\n");
	assertTrue(EQ(getDynArr(dyn, 2), 7), "Test 3rd element == 7");
	assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");

	printf("\n\nTesting swapDynArr...\nCalling swapDynArr(dyn, 2, 4)\n");
	swapDynArr(dyn, 2, 4);
	printf("The array's content: [3,4,6,5,7]\n");
	assertTrue(EQ(getDynArr(dyn, 2), 6), "Test 3rd element == 6");
	assertTrue(EQ(getDynArr(dyn, 4), 7), "Test 5th element == 7");

	printf("\n\nTesting removeAtDynArr...\nCalling removeAtDynArr(dyn, 1)\n");
	removeAtDynArr(dyn, 1);
	printf("The array's content: [3,6,5,7]\n");
	assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
	assertTrue(EQ(getDynArr(dyn, 3), 7), "Test 4th element == 7");
	assertTrue(sizeDynArr(dyn) == 4, "Test size = 4");

	printf("Testing shrinking\n");
	DynArr* d = createDynArr(10);
	for(int i=0;i<10;i++){
	  addDynArr(d,i+'a');
	}

	printDynArr(d);

	for(int i=0;i<8;i++){
	  removeAtDynArr(d,0);
	}

	printDynArr(d);
	assertTrue((d->capacity)<10, "Test resize");

	printf("DONE");
	return 0;
}
