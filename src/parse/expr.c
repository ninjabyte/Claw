#include <stdio.h>
#include <stdint.h>
#include "expr.h"
#include "leaf.h"
#include "parse.h"
#include "../error/error.h"
#include "../lex/lex.h"
#include "../cpl/cpl.h"

/* expression node */
void parse_expr(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (ps->token == TK_MINUS)	/* unary minus */
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

/* terminator node */
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

/* factor node */
void parse_factor(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (ps->token == TK_NUMBER) {
		leaf_int(ps);
		parse_next(ps);
	}else if (parse_accept(ps, TK_BR_OPEN)) {
		parse_expr(ps);
		parse_expect(ps, TK_BR_CLOSE);
	}else
		ps->error = ERR_SYNTAX;
}
