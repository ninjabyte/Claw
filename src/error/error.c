#include <stdio.h>
#include "error.h"

// error messages
const char* error_messages[] =
{
	"No errors occurred",
	"Invalid file",
	"Unexpected input",
	"Unexpected end of input",
	"Invalid escape sequence",
};

// prints the error message of an error code
void error_printmsg(int code)
{
	if (!code)
		fprintf(stderr, "%s\n", error_messages[0]);
	else if (code < NUM_ERRORS && code > ERR_NO_ERROR)
		fprintf(stderr, "Error: %s\n", error_messages[code]);
}
