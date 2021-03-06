#include "pch.h"
#include "Utils.h"
#include <iostream>

// Logic forward declaration

int main()
{
	void* invisibleLeak = malloc(1);
	
	MallocDebug_Init();

	// This pointer should get memory warning since it's not freed
	// using custom free
	void* leak = malloc(16);

	// Test int allocation
	int* mallocTest = (int*)malloc(sizeof(int));
	*mallocTest = 10;

	if (*mallocTest != 10) exit(1);

	// Test array of ints
	int* arrayOfInts = (int*)calloc(13, sizeof(int));
	
	// Fill the memory with data
	for (int i = 0; i < 13; i++) arrayOfInts[i] = 12-i;
	// Test the memory
	for (int i = 0; i < 13; i++)
		if (arrayOfInts[i] != 12 - i) exit(1);

	// Try reallocation
	// This pointer should not be marked as leak since it's
	// reallocated.
	int* toBeRealloced = (int*)malloc(sizeof(int));
	*toBeRealloced = 10;

	int* realloced = (int*)realloc(toBeRealloced, 2 * sizeof(int));
	if (realloced[0] != 10) exit(1);

	free(mallocTest);
	free(arrayOfInts);
	free(realloced);

	MallocDebug_Done();

	free(leak);
}
