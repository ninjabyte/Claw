#include <stdio.h>
#include <stdint.h>
#include "parse.h"
#include "../error/error.h"
#include "../lex/lex.h"
#include "../cpl/cpl.h"
#include "expr.h"

void parse_statement(ParseState* ps);

/* initializes a parser state */
void parse_init(ParseState* ps, LexState* ls, CplState* cs)
{
	ps->ls = ls;
	ps->cs = cs;
	ps->token = TK_NONE;
	ps->error = ERR_NO_ERROR;
}

void parse_logError(ParseState* ps)
{
	if (ps->ls->error)
		error_printmsgln(ps->ls->error, ps->ls->line);
	else if (ps->error)
		error_printmsgln(ps->error, ps->ls->line);
	else
		error_printmsg(ERR_NO_ERROR);
}

/* returns true if this parser is in an error state. */
uint8_t parse_hasError(ParseState* ps)
{
	return (ps->ls->error || ps->error);
}

/* get the next useful token, filtering out useless tokens like whitespace, newline and comments. */
void parse_next(ParseState* ps)
{
	if (parse_hasError(ps)) return;
	token_t tok = TK_NONE;
	do {
		tok = lex_next(ps->ls);
		//lex_debugPrintToken(ps->ls, tok);
	} while (ps->ls->in_comment || tok == TK_WHITESPACE || tok == TK_NEWLINE);
	ps->token = tok;
}

uint8_t parse_accept(ParseState* ps, token_t tok)
{
	if (ps->token == tok)
	{
		parse_next(ps);
		return 1;
	}
	return 0;
}

uint8_t parse_expect(ParseState* ps, token_t tok)
{
	if (parse_accept(ps, tok))
		return 1;
	ps->error = ERR_SYNTAX;
	return 0;
}

/* the program root node */
void parse_prog(ParseState* ps)
{
	if (parse_hasError(ps)) return;
	do {
		parse_next(ps);
		parse_expr(ps);
	} while (ps->token != TK_EOI && !parse_hasError(ps));
}

// statement node.
void parse_statement(ParseState* ps)
{
	//TODO assignment
	//TODO functioncall
	//TODO functiondef
	//TODO whileloop
	//TODO forloop
	//TODO ifstat
}
