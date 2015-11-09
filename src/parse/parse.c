#include <stdio.h>
#include <stdint.h>
#include "parse.h"
#include "../error/error.h"
#include "../lex/lex.h"
#include "../cpl/cpl.h"

void parse_next(ParseState* ps);
uint8_t parse_accept(ParseState* ps, token_t tok);
uint8_t parse_expect(ParseState* ps, token_t tok);

void parse_prog(ParseState* ps);
void parse_expr(ParseState* ps);
void parse_term(ParseState* ps);
void parse_int(ParseState* ps);
void parse_factor(ParseState* ps);

// initializes a parser state
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

// returns true if this parser is in an error state.
uint8_t parse_hasError(ParseState* ps)
{
	return (ps->ls->error || ps->error);
}

// get the next useful token, filtering out useless tokens like whitespace, newline and comments.
void parse_next(ParseState* ps)
{
	if (parse_hasError(ps)) return;
	token_t tok = TK_NONE;
	do {
		tok = lex_next(ps->ls);
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

void parse_parse(ParseState* ps)
{
	parse_prog(ps);
}

// the program root node
void parse_prog(ParseState* ps)
{
	if (parse_hasError(ps)) return;
	do {
		parse_next(ps);
		parse_expr(ps);
	} while (ps->token != TK_EOI && !parse_hasError(ps));
}

//TODO move these to another file, and move leaves to another file too

// expression node
void parse_expr(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (ps->token == TK_MINUS)	// unary minus
	{
		parse_next(ps);
		parse_term(ps);
		printf("(-)");
	}else
		parse_term(ps);

	while((ps->token == TK_PLUS || ps->token == TK_MINUS) && !parse_hasError(ps)) {
		token_t t = ps->token;
		parse_next(ps);
		parse_term(ps);

		if (t == TK_PLUS)
			printf("+");
		if (t == TK_MINUS)
			printf("-");
	}
}

// terminator node
void parse_term(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_factor(ps);
	while ((ps->token == TK_MULTIPLY || ps->token == TK_DIVIDE) && !parse_hasError(ps)) {
		token_t t = ps->token;
		parse_next(ps);
		parse_factor(ps);

		if (t == TK_MULTIPLY)
			printf("*");
		if (t == TK_DIVIDE)
			printf("/");
	}
}

// factor node
void parse_factor(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (parse_accept(ps, TK_NUMBER))
		parse_int(ps);
	else if (parse_accept(ps, TK_BR_OPEN))
	{
		parse_expr(ps);
		parse_expect(ps, TK_BR_CLOSE);
	}
	else
		ps->error = ERR_SYNTAX;
}

// integer leaf
void parse_int(ParseState* ps)
{
	if (parse_hasError(ps))
		return;

	printf("%d", ps->ls->kf.number);
}
