#include "variable.h"

typedef enum { namePlaceholder, character, integer, floating, string } varType;


#define floatMaxDecimals 16

/*
	VAR_printFloat
	---------------------------------------------------------------------
	Prints a float with the right number of decimals
	---------------------------------------------------------------------
	PARAMETERS:
		- f: the number to be printed
*/
void VAR_printFloat(double f);


struct var_t {
	varType type;
	char* varName;  // Here is the name of the variable (the value is somewhere else)

	// Here is the value of the variable
	int intVal;
	char charVal;
	double floatVal;
	char* strVal;
};

Variable VAR_parse(Common common, char firstChar) {
	Variable v;
	int decimalDigitsCounter = 0;
	int intPart = 0;
	long long unsigned floatPart = 0, floatConverter = 1;
	double val = 0;
	double tmp;
	char c;

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

			DS_readChar(common->string, common->file, false);
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			c = firstChar;
			// parse the integer part
			do {
				intPart *= 10;
				intPart += c - '0';
				c = DS_readChar(common->string, common->file, false);
			} while(c <= '9' && c >= '0');

			// if present, parse the decimal part
			if(c == '.') {
				c = DS_readChar(common->string, common->file, false);

				if(c <= '9' && c >= '0') do {
						decimalDigitsCounter++;
						floatPart *= 10;
						floatPart += c - '0';
						floatConverter *= 10;
						c = DS_readChar(common->string, common->file, false);
					} while(c <= '9' && c >= '0' && decimalDigitsCounter < floatMaxDecimals);

				while(c <= '9' && c >= '0') c = DS_readChar(common->string, common->file, false);

				v->type = floating;
				v->floatVal = intPart + (double) floatPart / floatConverter;
			} else {
				v->type = integer;
				v->intVal = intPart;
			}
			// c = firstChar;
			// // parse the integer part
			// do {
			// 	val *= 10;
			// 	val += c - '0';
			// 	c = DS_readChar(common->string, common->file, false);
			// } while(c <= '9' && c >= '0');

			// // if present, parse the decimal part
			// if(c == '.') {
			// 	c = DS_readChar(common->string, common->file, false);

			// 	if(c <= '9' && c >= '0') do {
			// 			tmp = c - '0';
			// 			for(int i = 0; i < floatConverter; i++) tmp /= 10;
			// 			val += tmp;
			// 			floatConverter += 1;
			// 			c = DS_readChar(common->string, common->file, false);
			// 		} while(c <= '9' && c >= '0');

			// 	v->type = floating;
			// 	v->floatVal = val;
			// } else {
			// 	v->type = integer;
			// 	v->intVal = intPart;
			// }
	}

	fseek(common->file, -1, SEEK_CUR);
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
		case floating: VAR_printFloat(v->floatVal); break;
		case string: printf("%s", v->strVal); break;
	}
}

void VAR_printFloat(double f) {
	char zeroDotDecimal[floatMaxDecimals + 1];
	char* onlyDecimal = zeroDotDecimal + 2;
	double fCopy = 10 * (f - (int) f);
	int i;

	sprintf(zeroDotDecimal, "%.16f", f - (int) f);

	for(i = floatMaxDecimals - 1; i > 0 && onlyDecimal[i] == '0'; i--) {}
	onlyDecimal[i + 1] = '\0';

	printf("%d.%s", (int) f, onlyDecimal);
}
