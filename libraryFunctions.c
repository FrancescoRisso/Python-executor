#include "libraryFunctions.h"

bool LIBFN_print(List argsList){
	Variable *args;
	int len, i;

	len = LIST_getVariableArray(argsList, &args);

	if(i<0) return false;
	for(i=0; i<len; i++){
		if(VAR_isValueHere(args[i])) VAR_print(args[i]);
		printf(" ");
	}
	printf("\n");

	free(args);
	
	return true;
}
