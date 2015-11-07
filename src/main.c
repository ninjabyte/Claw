/*
 * main.c
 *
 *  Created on: 05.11.2015
 *      Author: Benedikt
 */

#include <stdlib.h>
#include "parser.h"
#include "io.h"
#include "error/error.h"
#include "string.h"

#include "rpn.h"

int main(int argc, char *argv[])
{
	if(argc < 2) {
		error("No file specified!");
		return -1;
	}
	error_printmsg(do_parse(argv[1]));
	return EXIT_SUCCESS;
}
