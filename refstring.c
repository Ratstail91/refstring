#include "refstring.h"

#include <string.h>

//memory allocation
static RefStringAllocatorFn allocate;

void setRefStringAllocatorFn(RefStringAllocatorFn allocator) {
	allocate = allocator;
}

//API
RefString* createRefString(const char* cstring) {
	size_t length = strlen(cstring);

	return createRefStringLength(cstring, length);
}

RefString* createRefStringLength(const char* cstring, size_t length) {
	//allocate the memory area (including metadata space)
	RefString* refString = allocate(NULL, 0, sizeof(size_t) + sizeof(int) + sizeof(char) * (length + 1));

	if (refString == NULL) {
		return NULL;
	}

	//set the data
	refString->refCount = 1;
	refString->length = length;
	strncpy(refString->data, cstring, refString->length);

	refString->data[refString->length] = '\0'; //string terminator

	return refString;
}

void deleteRefString(RefString* refString) {
	//decrement, then check
	refString->refCount--;
	if (refString->refCount <= 0) {
		allocate(refString, sizeof(size_t) + sizeof(int) + sizeof(char) * (refString->length + 1), 0);
	}
}

int countRefString(RefString* refString) {
	return refString->refCount;
}

size_t lengthRefString(RefString* refString) {
	return refString->length;
}

RefString* copyRefString(RefString* refString) {
	//Cheaty McCheater Face
	refString->refCount++;
	return refString;
}

RefString* deepCopyRefString(RefString* refString) {
	//create a new string, with a new refCount
	return createRefStringLength(refString->data, refString->length);
}

const char* toCString(RefString* refString) {
	return refString->data;
}

bool equalsRefString(RefString* lhs, RefString* rhs) {
	//same pointer
	if (lhs == rhs) {
		return true;
	}

	//different length
	if (lhs->length != rhs->length) {
		return false;
	}

	//same string
	return strncmp(lhs->data, rhs->data, lhs->length) == 0;
}

bool equalsRefStringCString(RefString* lhs, char* cstring) {
	//get the rhs length
	size_t length = strlen(cstring);

	//different length
	if (lhs->length != length) {
		return false;
	}

	//same string
	return strncmp(lhs->data, cstring, lhs->length) == 0;
}