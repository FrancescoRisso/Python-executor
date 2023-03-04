#ifndef _DYNAMIC_STRING_H_

#define _DYNAMIC_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct DS_t* DynamicString;

/*
	DS_init
	---------------------------------------------------------------------
	Allocates all the memory for a dynamic string
	---------------------------------------------------------------------
	OUTPUT:
		- the dynamic string itself
		- NULL if memory problems occurred
*/
DynamicString DS_init();

/*
	DS_addChar
	---------------------------------------------------------------------
	Adds a character to the length of the string
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string itself
		- c: the character to be added
	---------------------------------------------------------------------
	OUTPUT:
		- quits everything if memory allocation fails
*/
void DS_addChar(DynamicString ds, char c);

/*
	DS_dupeString
	---------------------------------------------------------------------
	Creates a duplicate of the current string
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string itself
	---------------------------------------------------------------------
	OUTPUT:
		- strdup(current string)
*/
char* DS_dupeString(DynamicString ds);

/*
	DS_reset
	---------------------------------------------------------------------
	Re-initializes the string to be empty
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string itself
*/
void DS_reset(DynamicString ds);

/*
	DS_readChar
	---------------------------------------------------------------------
	Adds a character to the string by reading it from a file descryptor.
	If the character is '\n', the file cursor is rolled back one char so
	that the '\n' will be read again
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string where to write
		- f: the file where to read
	---------------------------------------------------------------------
	OUTPUT:
		- the read character, if all went smoothly
		- quits everything if memory allocation fails
*/
char DS_readChar(DynamicString ds, FILE* f, bool ignoreSpaces);

/*
	DS_free
	---------------------------------------------------------------------
	Frees the memory of a dynamic string
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string itself
*/
void DS_free(DynamicString ds);

/*
	removeLastChar
	---------------------------------------------------------------------
	Removes the last character in the string
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the string where to operate
*/
void DS_removeLastChar(DynamicString ds);

/*
	DS_isEqualTo
	---------------------------------------------------------------------
	Checks if the current content of a dynamic string is equal to a given
	string
	---------------------------------------------------------------------
	PARAMETERS:
		- ds: the dynamic string
		- str: the given string
	---------------------------------------------------------------------
	OUTPUT:
		- the result of the comparison
*/
bool DS_isEqualTo(DynamicString ds, const char*str);

#endif
