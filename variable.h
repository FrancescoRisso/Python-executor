#ifndef _VARIABLE_H_

#define _VARIABLE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "dynamicString.h"

/*
	Variable has different meaning depending on where it is stored.
	- If a Variable is in the Scope, then it is a container for a value,
		in other words it is where a value is stored
	- Otherwhise, it is used as a parameter for functions and
		instructions: in this case the Variable contains either the name
		of the Variable in the Scope, or the value if it was hardcoded
		(eg in case of print("Hello"), "Hello" is saved here as string)
*/
typedef struct var_t *Variable;

/*
	VAR_parse
	---------------------------------------------------------------------
	Parses a variable or a value
	---------------------------------------------------------------------
	PARAMETERS:
		- common
		- firstChar: the first char (already read from stream)
	---------------------------------------------------------------------
	OUTPUT:
		- the variable
		- NULL if memory problems occurred
*/
Variable VAR_parse(Common common, char firstChar);

/*
	VAR_free
	---------------------------------------------------------------------
	Frees a variable
	---------------------------------------------------------------------
	PARAMETERS:
		- v: the variable to be freed
*/
void VAR_free(Variable v);

/*
	VAR_isValueHere
	---------------------------------------------------------------------
	Tells if the actual value of a variable is stored in this object, or
	if this is just a "name placeholder" for a variable whose value is
	stored somewhere else, in the scope
	---------------------------------------------------------------------
	PARAMETERS:
		- v: the variable
	---------------------------------------------------------------------
	OUTPUT:
		- true: the value is actually here
		- false: this is just the name 
*/
bool VAR_isValueHere(Variable v);

/*
	VAR_print
	---------------------------------------------------------------------
	Given a value-containing Variable (so that VAR_isValueHere(v) = true)
	prints its value to the screen, without breakline.
	If the variable is non-value-containing, nothing is done
	---------------------------------------------------------------------
	PARAMETERS:
		- v: the variable
*/
void VAR_print(Variable v);

#endif
