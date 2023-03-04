#include "dynamicString.h"

struct DS_t {
	int size;
	int len;
	char* string;
};


DynamicString DS_init() {
	DynamicString ds = malloc(sizeof(*ds));

	if(ds != NULL) {
		ds->string = malloc(2 * sizeof(char));
		ds->size = 1;
		ds->len = 0;
		ds->string[0] = '\0';
	}

	if(ds->string == NULL) {
		free(ds);
		ds = NULL;
	}

	return ds;
}

void DS_addChar(DynamicString ds, char c) {
	if(ds->len == ds->size) {
		ds->string = realloc(ds->string, (1 + 2 * ds->size) * sizeof(char));
		if(ds->string == NULL) exit(-1);
		ds->size *= 2;
	}

	ds->string[ds->len] = c;
	ds->string[++(ds->len)] = '\0';
}

char* DS_dupeString(DynamicString ds) {
	return strdup(ds->string);
}

void DS_reset(DynamicString ds) {
	ds->len = 0;
	ds->string[0] = '\0';
}

char DS_readChar(DynamicString ds, FILE* f, bool ignoreSpaces) {
	char c;
	fscanf(f, "%c", &c);
	if(ignoreSpaces && c == ' ') return ' ';
	DS_addChar(ds, c);
	if(c=='\n') fseek(f, -1, SEEK_CUR);
	return c;
}

void DS_free(DynamicString ds) {
	if(ds == NULL) return;

	if(ds->string != NULL) free(ds->string);
	free(ds);
}

void DS_removeLastChar(DynamicString ds) {
	if(ds->len == 0) return;

	ds->len--;
	ds->string[ds->len] = '\0';
}

bool DS_isEqualTo(DynamicString ds, const char* str) {
	if(strncmp(ds->string, str, ds->size) == 0) return true;
	return false;
}
