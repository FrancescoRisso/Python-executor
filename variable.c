#include "variable.h"

typedef enum { namePlaceholder, character, integer, floating, string } varType;

struct var_t {
	varType type;
	char* varName;  // Here is the name of the variable (the value is somewhere else)

	// Here is the value of the variable
	int intVal;
	char charVal;
	float floatVal;
	char* strVal;
};

Variable VAR_parse(Common common, char firstChar) {
	Variable v;
	bool hasDot = false;

	if((v = malloc(sizeof(*v))) == NULL) {
		printf("Could not allocate variable\n");
		return NULL;
	}

	v->varName = NULL;
	DS_reset(common->string);

	switch(firstChar) {
		case '\"':
			while(DS_readChar(common->string, common->file, false) != '\"') {}
			DS_removeLastChar(common->string);
			v->type = string;
			v->strVal = DS_dupeString(common->string);
			break;
	}

	return v;
}

void VAR_free(Variable v) {
	if(v == NULL) return;

	if(v->varName != NULL) free(v->varName);
	if(v->type == string) free(v->strVal);

	free(v);
}

bool VAR_isValueHere(Variable v) {
	return v->type != namePlaceholder;
}

void VAR_print(Variable v) {
	switch(v->type) {
		case namePlaceholder: break;
		case character: printf("%c", v->charVal); break;
		case integer: printf("%d", v->intVal); break;
		case floating: printf("%f", v->floatVal); break;
		case string: printf("%s", v->strVal); break;
	}
}
