#include "error.h"
#include "../io.h"

// error messages
const char* error_messages[] =
{
	"No errors occurred",
	"Invalid file"
	"Unexpected input",
	"Unexpected end of input",
	"Unexpected token",
	"Out of memory",
};

// prints the error message of an error code
void error_printmsg(int code)
{
	if (code < NUM_ERRORS && code >= ERR_NO_ERROR)
		error(error_messages[code]);
}
