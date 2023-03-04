#include "main.h"

int main(int argc, char *argv[]) {
	Common common;
	Instruction program;

	if((common = COM_init("input.py")) == NULL) return -1;

	program = INSTR_parse(common);

	INSTR_execute(program);

	INSTR_free(program);
	COM_free(common);

	return 0;
}
