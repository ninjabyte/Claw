/*
 ============================================================================
 Name        : parser.c
 Author      : Benedikt Müssig
 Version     : 0.1
 Copyright   : (c) 2015 Benedikt Müssig
 Description : Parser for the Claw language
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "parser.h"
#include "lex/lex.h"
#include "rpn.h"
#include "cpl/cpl.h"
#include "error/error.h"

// test the lexer
int do_parse(char* file)
{
	FILE* fp = fopen(file, "r");

	if(!fp)
	    return ERR_INVALID_FILE;

	LexState ls;
	lex_init(&ls, fp);

	while (!feof(fp))
	{
		int tok = lex_next(&ls);
		printf("%d", tok);
		if (tok == TK_NAME)
			printf(" name: %s", ls.kf.name);
		if (tok == TK_NUMBER)
			printf(" number: %d", ls.kf.number);
		if (tok == TK_NONE)
			break;
		printf("\n");
	}

	fclose(fp);
	return ERR_NO_ERROR;
}
