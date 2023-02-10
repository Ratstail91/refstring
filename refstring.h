#pragma once

#include <stdbool.h>
#include <stddef.h>

//memory allocation hook
typedef void* (*RefStringAllocatorFn)(void* pointer, size_t oldSize, size_t newSize);
void setRefStringAllocatorFn(RefStringAllocatorFn);

//the RefString structure
typedef struct RefString {
	size_t length;
	int refCount;
	char data[];
} RefString;

//API
RefString* createRefString(const char* cstring);
RefString* createRefStringLength(const char* cstring, size_t length);
void deleteRefString(RefString* refString);
int countRefString(RefString* refString);
size_t lengthRefString(RefString* refString);
RefString* copyRefString(RefString* refString);
RefString* deepCopyRefString(RefString* refString);
const char* toCString(RefString* refString);
bool equalsRefString(RefString* lhs, RefString* rhs);
bool equalsRefStringCString(RefString* lhs, char* cstring);
