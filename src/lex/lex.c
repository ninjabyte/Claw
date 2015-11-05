#include <stdio.h>
#include <string.h>
#include "lex.h"
#include "../error/error.h"
#include "token.h"

// get pointer to current location in source
#define getSrc(ls) ((char*) ((ls)->src + (ls)->current))

// initializes a lex state
void lex_init(LexState* ls, const char* src, size_t size)
{
	ls->src = src;
	ls->size = size;
	ls->current = 0;
	ls->line = 0;
	ls->error = ERR_NO_ERROR;
	ls->tok.token = TK_NONE;
	ls->tok.seq = src;
	ls->tok.seqlen = 0;
}

// print the error of a lex state
void lex_printerr(LexState *ls)
{
	error_printmsg(ls->error);
	if (ls->error)
		printf("at line: %i", ls->line);
}

int lex_isFinished(LexState* ls)
{
	return ls->current >= ls->size;
}

// tries to read the next token and add it to the queue. Will set ls.error if an error occured.
void lex_nextToken(LexState* ls)
{
	while (ls->tok.token == TK_NONE)
	{
		token_next(getSrc(ls), &ls->tok);
		if (ls->tok.token == TK_NONE)
		{
			ls->error = ERR_UNEXPECTED_INPUT;
			break;
		}else if(ls->tok.token == TK_NEWLINE)
		{
			ls->line++;
			ls->tok.token = TK_NONE;
		}else if(ls->tok.token == TK_COMMENT || ls->tok.token == TK_WHITESPACE)
			ls->tok.token = TK_NONE;
		ls->current += ls->tok.seqlen;
		if (lex_isFinished(ls))
			break;
	}
}
