#ifndef _FUNCTION_H_

#define _FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "list.h"
#include "variable.h"
#include "libraryFunctions.h"

typedef struct function_t* Function;

/*
	FUNCT_parse_call
	---------------------------------------------------------------------
	Creates a Function describing the function calling
	---------------------------------------------------------------------
	PARAMETERS:
		- name: the name of the function, inclusive of the '(' character
		- com
	---------------------------------------------------------------------
	OUTPUT:
		- the parsed Function call
*/
Function FUNCT_parse_call(char* name, Common common);

/*
	FUNCT_free
	---------------------------------------------------------------------
	Frees a function block
	---------------------------------------------------------------------
	PARAMETERS:
		- f: the function block to be freed
*/
void FUNCT_free(Function f);

/*
	FUNCT_execute
	---------------------------------------------------------------------
	Executes a function
	---------------------------------------------------------------------
	PARAMETERS:
		- f: the function
	---------------------------------------------------------------------
	OUTPUT:
		- true if all went smoothly, false if some problems occurred
*/
bool FUNCT_execute(Function f);


#endif
