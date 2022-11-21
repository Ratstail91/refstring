#include "refstring.h"

#include "console_colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//test allocator
static size_t allocatedMemory = 0;

static void* testAllocator(void* pointer, size_t oldSize, size_t newSize) {
	allocatedMemory -= oldSize;
	allocatedMemory += newSize;

	if (newSize == 0 && oldSize == 0) {
		return NULL;
	}

	if (newSize == 0) {
		free(pointer);
		return NULL;
	}

	void* mem = realloc(pointer, newSize);

	if (mem == NULL) {
		fprintf(stderr, ERROR "Memory allocation error (requested %d for %ld, replacing %d)\n" RESET, (int)newSize, (long int)pointer, (int)oldSize);
		exit(-1);
	}

	return mem;
}

int main() {
	//setup
	setCStringAllocatorFn(testAllocator);

	//run tests
	{
		//basic allocation & deletion
		RefString* str = createRefString("Hello world!");

		deleteRefString(str);
	}

	{
		//basic check the length is correct
		RefString* str = createRefString("Hello world!");

		if (lengthRefString(str) != 12) {
			return -1;
		}

		deleteRefString(str);
	}

	{
		//copy and free a refstring
		RefString* str1 = createRefString("Hello world!");
		RefString* str2 = copyRefString(str1);

		deleteRefString(str1);
		deleteRefString(str2); //every pointer must be cleared
	}

	{
		//deep copy and free a refstring
		RefString* str1 = createRefString("Hello world!");
		RefString* str2 = deepCopyRefString(str1);

		deleteRefString(str1);
		deleteRefString(str2); //every copy must be cleared
	}

	{
		//get the raw value
		RefString* str = createRefString("Hello world!");

		if (strncmp(toCString(str), "Hello world!", lengthRefString(str))) {
			return -1;
		}

		deleteRefString(str);
	}

	{
		//compare
		RefString* str1 = createRefString("Hello world!");
		RefString* str2 = createRefString("Hello world!");
		RefString* str3 = createRefString("Hello kayne!");

		//ascii "w" is larger than ascii "p"
		if (refStrEqual(str1, str2) == false) {
			return -1;
		}

		if (refStrEqual(str1, str3) == true) {
			return -1;
		}

		deleteRefString(str1);
		deleteRefString(str2);
		deleteRefString(str3); //every copy must be cleared
	}

	//cleanup
	if (allocatedMemory != 0) {
		fprintf(stderr, ERROR "Memory leak detected - lost %ld bytes\n" RESET, allocatedMemory);
		return 1;
	}

	fprintf(stdout, NOTICE "All good\n" RESET);
	return 0;
}
