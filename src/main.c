/*
 * main.c
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

#include <stdlib.h>
#include "parser.h"
#include "io.h"
#include "lex/lex.h"
#include "error/error.h"
#include "stdlib.h"

#include "rpn.h"

int main(int argc, char *argv[])
{
	char *str = "-192x";
	volatile char *outputQueue[strlen(str)];
	toRpn(str, outputQueue);

	if(argc < 2) {
		error("No file specified!");
		return -1;
	}
	error_printmsg(lex_test(argv[1]));
	return EXIT_SUCCESS;
}
