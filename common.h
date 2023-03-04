#ifndef _COMMON_H_

#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#include "dynamicString.h"

struct common_t {
	DynamicString string;
	FILE* file;
	void* errorPtr;
	char indentChar;
	int indentCharCnt;
	int currentIndent;
};

typedef struct common_t* Common;

typedef enum {correct, incorrect, eof} indentCorrectness;

/*
	COM_init
	---------------------------------------------------------------------
	Creates everything needed for the whole program
	---------------------------------------------------------------------
	PARAMETERS:
		- fName: the name of the file to be read
	---------------------------------------------------------------------
	OUTPUT:
		- The common item
		- NULL if problems occurred
*/
Common COM_init(char* fName);

/*
	COM_free
	---------------------------------------------------------------------
	Frees a common item
	---------------------------------------------------------------------
	PARAMETERS:
		- com: the item to be freed
*/
void COM_free(Common com);

/*
	COM_parseIndent
	---------------------------------------------------------------------
	Reads the indentation, checking it is correct
	---------------------------------------------------------------------
	PARAMETERS:
		- common
	---------------------------------------------------------------------
	OUTPUT:
		- true if it was correct, false if the indenting was wrong
*/
indentCorrectness COM_parseIndent(Common common);


#endif
