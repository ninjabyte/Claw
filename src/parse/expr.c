#include <stdio.h>
#include <stdint.h>
#include "expr.h"
#include "parse.h"
#include "../error/error.h"
#include "../lex/lex.h"
#include "../cpl/cpl.h"
#include "parseutil.h"

/* expression node */
void parse_expr(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_equilisator(ps);
}

/* equilisator node: == and != */
void parse_equilisator(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_comparators(ps);
	while (!parse_hasError(ps)) {
		if (parse_accept(ps, TK_EQUALS)) {
			parse_comparators(ps);
			leaf_operator(OP_EQUALS);
		} else if(parse_accept(ps, TK_INEQUALS)) {
			parse_comparators(ps);
			leaf_operator(OP_INEQUALS);
		} else
			break;
	}
}
/* comparison node: < <= >= >*/
void parse_comparators(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_shift(ps);
	while (!parse_hasError(ps)) {
		if (parse_accept(ps, TK_LESS)) {
			parse_shift(ps);
			leaf_operator(OP_LESS);
		} else if(parse_accept(ps, TK_LESSEQUALS)) {
			parse_shift(ps);
			leaf_operator(OP_LESSEQUALS);
		} else if(parse_accept(ps, TK_GREATER)) {
			parse_shift(ps);
			leaf_operator(OP_GREATER);
		} else if(parse_accept(ps, TK_GREATEREQUALS)) {
			parse_shift(ps);
			leaf_operator(OP_GREATEREQUALS);
		} else
			break;
	}
}

/* bit shift node: << or >> */
void parse_shift(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_plusminus(ps);
	while (!parse_hasError(ps)) {
		if (parse_accept(ps, TK_BIT_SL)) {
			parse_plusminus(ps);
			leaf_operator(OP_BIT_SL);
		} else if(parse_accept(ps, TK_BIT_SR)) {
			parse_plusminus(ps);
			leaf_operator(OP_BIT_SR);
		} else
			break;
	}
}

/* plusminus node: + or -*/
void parse_plusminus(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_multdivmod(ps);
	while (!parse_hasError(ps)) {
		if (parse_accept(ps, TK_PLUS)) {
			parse_multdivmod(ps);
			leaf_operator(OP_ADD);
		} else if(parse_accept(ps, TK_MINUS)) {
			parse_multdivmod(ps);
			leaf_operator(OP_SUBTRACT);
		} else
			break;
	}
}

/* terminator node: *, / or % */
void parse_multdivmod(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	parse_unary(ps);
	while (!parse_hasError(ps)) {
		if (parse_accept(ps, TK_MULTIPLY)) {
			parse_unary(ps);
			leaf_operator(OP_MULTIPLY);
		} else if(parse_accept(ps, TK_DIVIDE)) {
			parse_unary(ps);
			leaf_operator(OP_DIVIDE);
		} else if(parse_accept(ps, TK_MODULUS)) {
			parse_unary(ps);
			leaf_operator(OP_MODULUS);
		} else
			break;
	}
}

/* unary node: - or !*/
void parse_unary(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (parse_accept(ps, TK_MINUS)) {/* unary minus */
		parse_factor(ps);
		leaf_operator(OP_UNARY_MINUS);
	} else if (parse_accept(ps, TK_BIT_NOT)) { /* unary not */
		parse_factor(ps);
		leaf_operator(OP_UNARY_BIT_NOT);
	} else
		parse_factor(ps);
}

/* factor node */
void parse_factor(ParseState* ps)
{
	if (parse_hasError(ps)) return;

	if (ps->token == TK_NUMBER) {
		leaf_int(ps->ls->kf.number);
		parse_next(ps);
	} else if (parse_accept(ps, TK_BR_OPEN)) {
		parse_expr(ps);
		parse_expect(ps, TK_BR_CLOSE);
	} else
		ps->error = ERR_SYNTAX;
}

/* operator leaf */
void leaf_operator(operator_t operator)
{
	switch(operator) {
		case OP_UNARY_MINUS:	/* - */
			printf("(-)");
			break;
		case OP_ADD:			/* + */
			printf("+");
			break;
		case OP_SUBTRACT:		/* - */
			printf("-");
			break;
		case OP_MULTIPLY:		/* * */
			printf("*");
			break;
		case OP_DIVIDE:			/* / */
			printf("/");
			break;
		case OP_MODULUS:		/* % */
			printf("%%");
			break;
		case OP_LESS:			/* < */
			printf("<");
			break;
		case OP_GREATER:		/* > */
			printf(">");
			break;
		case OP_LESSEQUALS:		/* <= */
			printf("(<=)");
			break;
		case OP_GREATEREQUALS:	/* >= */
			printf("(>=)");
			break;
		case OP_EQUALS:			/* == */
			printf("(==)");
			break;
		case OP_INEQUALS:		/* != */
			printf("(!=)");
			break;
		case OP_AND:			/* && */
			printf("(&&)");
			break;
		case OP_OR:				/* || */
			printf("(||)");
			break;
		case OP_BIT_OR:			/* | */
			printf("|");
			break;
		case OP_BIT_AND:		/* & */
			printf("&");
			break;
		case OP_UNARY_BIT_NOT:	/* ! */
			printf("(!)");
			break;
		case OP_BIT_SL:			/* << */
			printf("<<");
			break;
		case OP_BIT_SR:			/* >> */
			printf(">>");
			break;
		case OP_BIT_XOR:		/* ^ */
			printf("^");
			break;
	}
}

/* integer leaf */
void leaf_int(uint16_t number)
{
	printf("%d", number);
}
