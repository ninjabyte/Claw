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

// parse code
int do_compile(char* input_file, char* output_file, CplHeader* ch)
{
	FILE* ifp = fopen(input_file, "r");
	FILE* ofp = fopen(output_file, "w");

	if(!ifp || !ofp)
	    return ERR_INVALID_FILE;

	LexState ls;
	lex_init(&ls, ifp);

	CplState cs;
	cpl_init(&cs, ch, ofp);

	cpl_write_header(&cs);

	while (!feof(ifp))
	{
		int tok = lex_next(&ls);

		switch(tok) {
		case TK_NAME:
			printf("name: %s", ls.kf.name);
			break;
		case TK_CHARACTER:
			cpl_write_arg8(&cs, ls.kf.character);
			if (ls.kf.character > 32) {
				printf("char: %c", ls.kf.character);
			} else if(ls.kf.character == 32) {
				printf("char: (space)");
			} else
				printf("char: 0x%02hhX", ls.kf.character);
			break;
		case TK_NUMBER:
			printf(" number: %d", ls.kf.number);
			break;
		default:
			if(tok >= TOK_FIRST_KW && tok <= TOK_LAST_KW)
				printf("keyword: %s", lex_getKeywordString(tok));
			else
				printf("token: %d", tok);
			break;
		}
		printf("\n");
	}

	fclose(ifp);
	fclose(ofp);
	return ERR_NO_ERROR;
}

// parse code
int do_debug_parse(char* file)
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
		if (tok >= TOK_FIRST_KW && tok <= TOK_LAST_KW)
			printf(" keyword: %s", lex_getKeywordString(tok));
		if (tok == TK_CHARACTER)
		{
			if (ls.kf.character > 32)
				printf(" char: %c", ls.kf.character);
			else if(ls.kf.character == 32) {
				printf(" char: (space)");
			} else
				printf(" char: 0x%02hhX", ls.kf.character);
		}
		if (tok == TK_NONE)
			break;
		printf("\n");
	}

	fclose(fp);
	return ERR_NO_ERROR;
}
