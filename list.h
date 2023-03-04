#ifndef _LIST_H_

#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "variable.h"

typedef enum { functions, variables, strings } listType;

typedef struct list_t* List;

/*
	LIST_init
	---------------------------------------------------------------------
	Creates a new list
	---------------------------------------------------------------------
	PARAMETERS:
		- type: the type of objects in the list
	---------------------------------------------------------------------
	OUTPUT:
		- the list itself, if all went smoothly
		- NULL if something went wrong
*/
List LIST_init(listType type);

/*
	LIST_free	TODO
	---------------------------------------------------------------------
	Frees the memory of a list
	---------------------------------------------------------------------
	PARAMETERS:
		- l: the list to be freed
		- alsoFreeItems: whether its items should be freed, too
*/
void LIST_free(List l, bool alsoFreeItems);

/*
	LIST_appendVariable
	---------------------------------------------------------------------
	Appends a variable to a list of variables
	---------------------------------------------------------------------
	PARAMETERS:
		- l: the list where to append
		- v: the variable to append
	---------------------------------------------------------------------
	OUTPUT:
		- true if all went smoothly, false if some problems occurred
*/
bool LIST_appendVariable(List l, Variable v);

/*
	LIST_getVariableArray
	---------------------------------------------------------------------
	Creates (and allocates) an array containing the variables in the list
	and returns the lenght
	---------------------------------------------------------------------
	PARAMETERS:
		- l: the variables list to convert to array
		- arrayPtr: a pointer to where to create the array
	---------------------------------------------------------------------
	OUTPUT:
		- the length of the array
		- -1 if the list was not of type variables
		- -2 if unable to allocate memory
*/
int LIST_getVariableArray(List l, Variable **arrayPtr);

#endif
