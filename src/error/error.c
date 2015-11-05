#include <stdio.h>
#include "error.h"

// error messages
const char* error_messages[] =
{
	"No error occured",
	"Unexpected input",
	"Unexpected end of input",
	"Unexpected token",
	"Out of memory",
};

// prints the error message of an error code
void error_printmsg(unsigned int code)
{
	if (code == ERR_NO_ERROR)
		printf("%s\n", error_messages[code]);
	else if (code < NUM_ERRORS && code > ERR_NO_ERROR)
		printf("Error: %s (Error code %i)\n", error_messages[code], code);
}
