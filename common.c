#include "common.h"

/*
	COM_error_free
	---------------------------------------------------------------------
	Frees a common item and prints an error message
	---------------------------------------------------------------------
	PARAMETERS:
		- com: the common item
		- mess: the message that will be inserted in:
			"Could not {...}. Aborting\n"
	---------------------------------------------------------------------
	OUTPUT:
		- NULL (ready to be returned)
*/
void* COM_error_free(Common com, char* mess);

Common COM_init(char* fName) {
	Common com = malloc(sizeof(*com));
	if(com == NULL) return COM_error_free(com, "allocate common");

	com->string = NULL;
	com->file = NULL;
	com->errorPtr = NULL;
	com->indentChar = '-';
	com->indentCharCnt = -1;
	com->currentIndent = 0;

	if((com->string = DS_init()) == NULL) return COM_error_free(com, "allocate dynamic string");
	if((com->file = fopen(fName, "r")) == NULL) return COM_error_free(com, "open input file");
	if((com->errorPtr = malloc(sizeof(char))) == NULL) return COM_error_free(com, "allocate 'invalid value' pointer");

	return com;
}


void COM_free(Common com) {
	if(com == NULL) return;

	if(com->string != NULL) DS_free(com->string);
	if(com->errorPtr != NULL) free(com->errorPtr);
	if(com->file != NULL) fclose(com->file);

	free(com);
}


void* COM_error_free(Common com, char* mess) {
	COM_free(com);
	printf("Could not %s. Aborting\n", mess);
	return NULL;
}


indentCorrectness COM_parseIndent(Common common) {
	// The last read char is a '\n'
	char c;

	fscanf(common->file, "%c", &c);

	// If file is finished, notify about that
	if(feof(common->file)) return eof;

	// If there is an empty line, parse the next line
	if(c == '\n') return COM_parseIndent(common);

	// switch(common->indentChar) {
	// 	case '-':
	// 		if(common->currentIndent != 1) return incorrect;
	// 		common->indentChar = c;
	// 		for(; c == common->indentChar; common->indentCharCnt++) fscanf(common->file, "%c", &c);
	// }

	fseek(common->file, -1, SEEK_CUR);
	return correct;
}
