#include "instruction.h"

#include "function.h"

typedef enum { invalid, function, endOfChain } instructionType;

struct instruction_t {
	instructionType type;

	Instruction next;

	Function funct;
};

/*
	INSTR_err_free
	---------------------------------------------------------------------
	Frees an instruction item and prints an error message
	---------------------------------------------------------------------
	PARAMETERS:
		- i: the instruction
		- mess: the message that will be inserted in:
			"Could not {...}. Aborting\n"
			or NULL to avoid the printing
		- common
	---------------------------------------------------------------------
	OUTPUT:
		- the error instruction type
*/
void* INSTR_err_free(Instruction i, char* mess, Common common);


Instruction INSTR_parse(Common common) {
	bool readFinished = false;
	Instruction instr;
	indentCorrectness indent;

	instr = malloc(sizeof(*instr));
	if(instr == NULL) return NULL;

	instr->next = NULL;
	instr->funct = NULL;
	instr->type = endOfChain;

	DS_reset(common->string);

	while(!readFinished) {
		switch(DS_readChar(common->string, common->file, true)) {
			case '(':
				if(DS_isEqualTo(common->string, "(")) {
					// Can be operation, multiple assignment (?), ...
				} else {
					// Function call
					readFinished = true;
					instr->funct = FUNCT_parse_call(DS_dupeString(common->string), common);
					instr->type = instr->funct == NULL ? invalid : function;
				}
				break;
			case '\n':
				indent = COM_parseIndent(common);
				if(indent == incorrect) return INSTR_err_free(instr, NULL, common);
				if(indent == eof) readFinished = true;
				else DS_removeLastChar(common->string);
				break;
		}
	}

	if(instr->type == invalid) return INSTR_err_free(instr, "allocate instruction values", common);

	if(instr->type != endOfChain) {
		instr->next = INSTR_parse(common);
		if(instr->next == NULL || instr->next->type == invalid) return INSTR_err_free(instr, NULL, common);
	}

	return instr;
}

void INSTR_free(Instruction i) {
	if(i == NULL) return;

	if(i->next != NULL) INSTR_free(i->next);

	if(i->type == function) FUNCT_free(i->funct);
	
	free(i);
}

void* INSTR_err_free(Instruction i, char* mess, Common common) {
	INSTR_free(i);
	if(mess != NULL) printf("Could not %s. Aborting\n", mess);
	return common->errorPtr;
}

bool INSTR_execute(Instruction i) {
	switch(i->type) {
		case invalid: return false;
		case endOfChain: return true;
		case function: FUNCT_execute(i->funct);
	}
	INSTR_execute(i->next);
}
