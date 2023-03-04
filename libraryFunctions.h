#ifndef _LIB_FN_H_

#define _LIB_FN_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "variable.h"

/*
	LIBFN_print
	---------------------------------------------------------------------
	Executes a standard print
	---------------------------------------------------------------------
	PARAMETERS:
		- f: list of arguments
	---------------------------------------------------------------------
	OUTPUT:
		- true if all went smoothly, false if some problems occurred
*/
bool LIBFN_print(List argsList);

#endif
