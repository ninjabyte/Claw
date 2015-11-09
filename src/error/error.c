#include <stdio.h>
#include "error.h"

/* error messages */
const char* error_messages[] =
{
	"No errors occurred",
	"Invalid file",
	"Unexpected input",
	"Unexpected end of input",
	"Invalid escape sequence",
	"Syntax",
};

/* prints the error message of an error code */
void error_printmsg(int code)
{
	if (!code)
		fprintf(stderr, "%s\n", error_messages[0]);
	else if (code < NUM_ERRORS && code > ERR_NO_ERROR)
		fprintf(stderr, "Error: %s\n", error_messages[code]);
}

/* prints the error message of an error code, with the line the error is at. */
void error_printmsgln(int code, int line)
{
	error_printmsg(code);
	if (code)
		fprintf(stderr, "at line %d\n", line);
}

