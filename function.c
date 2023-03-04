#include "function.h"

typedef enum { custom, print } functionType;

struct function_t {
	functionType type;
	char* functName;
	List argsList;
};

/*
	FUNCT_err_free
	---------------------------------------------------------------------
	Frees a function item and prints an error message
	---------------------------------------------------------------------
	PARAMETERS:
		- f: the function
		- mess: the message that will be inserted in:
			"Could not {...}. Aborting\n"
	---------------------------------------------------------------------
	OUTPUT:
		- NULL (ready to be returned)
*/
void* FUNCT_err_free(Function f, char* mess);


Function FUNCT_parse_call(char* name, Common common) {
	char c;
	Function funct;
	Variable v;

	if((funct = malloc(sizeof(*funct))) == NULL) return FUNCT_err_free(funct, "allocate function");

	funct->functName = name;

	// Understand type of function
	if(strcmp(name, "print(") == 0) { funct->type = print; }

	// Read the parameters
	funct->argsList = LIST_init(variables);
	while((c = DS_readChar(common->string, common->file, true)) != ')') {
		if(c == ' ' || c == ',') continue;
		if((v = VAR_parse(common, c)) == NULL) return FUNCT_err_free(funct, "read function parameters");
		if(!LIST_appendVariable(funct->argsList, v)) {
			VAR_free(v);
			return FUNCT_err_free(funct, "add variable to the parameter list");
		}
	}

	return funct;
}

void* FUNCT_err_free(Function f, char* mess) {
	FUNCT_free(f);
	printf("Could not %s. Aborting\n", mess);
	return NULL;
}

void FUNCT_free(Function f) {
	if(f == NULL) return;

	if(f->functName != NULL) free(f->functName);
	if(f->argsList != NULL) LIST_free(f->argsList, true);
	free(f);
}

bool FUNCT_execute(Function f) {
	switch(f->type) {
		case print: return LIBFN_print(f->argsList);
	}
}
