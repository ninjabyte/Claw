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
#include "cpl/cpl.h"

#include "rpn.h"

int main(int argc, char *argv[])
{
	if(argc < 2) {
		error("No file specified!");
		return -1;
	}

	CplPermissions cp;
	CplHeader ch;
	strcpy(ch.name, "Hello World");
	strcpy(ch.author, "ninjabyte");
	ch.version[VER_MAJOR] = 1;
	ch.version[VER_MINOR] = 0;
	ch.version[VER_REVISION] = 0;
	ch.permissions = cp;

	do_compile(argv[1], "a.out", &ch);
	return EXIT_SUCCESS;
}
