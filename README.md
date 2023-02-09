# refstring

A c-string wrapper library designed for efficient memory management.

This library allows you to pass strings by reference rather than value, and reduces string copying by allowing copies of RefStrings to point to the original. Also allows for custom memory allocation.

```c
RefString* str = createRefString("Hello world!");

printf("%s", toCString( str ));

deleteRefString(str);
```

## Features

* Custom allocator support
* Efficient memory management
* Fully battle tested and open source

## Usage

Before using this utility, you must first set the memory allocator.

Be sure to always delete a `RefString` after use.

```c
//here is an allocator function that you can use
static void* exampleAllocator(void* pointer, size_t oldSize, size_t newSize) {
	if (newSize == 0 && oldSize == 0) {
		return NULL;
	}

	if (newSize == 0) {
		free(pointer);
		return NULL;
	}

	void* mem = realloc(pointer, newSize);

	if (mem == NULL) {
		fprintf(stderr, "Memory allocation error (requested %zu, replacing %zu)\n", newSize, oldSize);
	}

	return mem;
}

//run your program
#include "refstring.h"

int main() {
	setRefStringAllocatorFn(exampleAllocator);

	//TODO: do stuff

	return 0;
}
```
