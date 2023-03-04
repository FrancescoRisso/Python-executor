#ifndef _INSTRUCTION_H_

#define _INSTRUCTION_H_

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

typedef struct instruction_t *Instruction;

/*
	INSTR_parse
	---------------------------------------------------------------------
	Reads a file and creates a set of Instructions describing it
	---------------------------------------------------------------------
	PARAMETERS:
		- common
	---------------------------------------------------------------------
	OUTPUT:
		- A chain of Instructions describing the program
		- NULL if something went wrong
*/
Instruction INSTR_parse(Common common);

/*
	INSTR_free
	---------------------------------------------------------------------
	Frees an instruction block
	---------------------------------------------------------------------
	PARAMETERS:
		- i: the instruction to be freed
*/
void INSTR_free(Instruction i);

/*
	INSTR_execute
	---------------------------------------------------------------------
	Executes an instruction and all the following ones
	---------------------------------------------------------------------
	PARAMETERS:
		- i: the instruction
	---------------------------------------------------------------------
	OUTPUT:
		- true if all went smoothly, false if some problems occurred
*/
bool INSTR_execute(Instruction i);


#endif
