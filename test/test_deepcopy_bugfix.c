#include "refstring.h"

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
		fprintf(stderr, "Memory allocation error (requested %d for %ld, replacing %d)\n", (int)newSize, (long int)pointer, (int)oldSize);
		exit(-1);
	}

	return mem;
}

int main() {
	//setup
	setRefStringAllocatorFn(testAllocator);

	{
		RefString* str1 = createRefString("Hello world");
		RefString* str2 = copyRefString(str1);

		//BUGFIX: test that deepCopyRefString doesn't copy the refcount
		RefString* test = deepCopyRefString(str1);

		deleteRefString(str1);
		deleteRefString(str2);
		deleteRefString(test);
	}

	//cleanup
	if (allocatedMemory != 0) {
		fprintf(stderr, "Memory leak detected - lost %ld bytes\n", allocatedMemory);
		return 1;
	}

	fprintf(stdout, "All good\n");
	return 0;
}
