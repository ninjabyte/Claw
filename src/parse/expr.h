#ifndef EXPR_H_
#define EXPR_H_

#include <stdint.h>
#include "parse.h"

enum Operator
{
	OP_UNARY_MINUS,		/* - */
	OP_ADD,				/* + */
	OP_SUBTRACT,		/* - */
	OP_MULTIPLY,		/* * */
	OP_DIVIDE,			/* / */
	OP_MODULUS,			/* % */
	OP_LESS,			/* < */
	OP_GREATER,			/* > */
	OP_LESSEQUALS,		/* <= */
	OP_GREATEREQUALS,	/* >= */
	OP_EQUALS,			/* == */
	OP_INEQUALS,		/* != */
	OP_AND,				/* && */
	OP_OR,				/* || */
	OP_UNARY_NOT,		/* ! */
	OP_BIT_OR,			/* | */
	OP_BIT_AND,			/* & */
	OP_UNARY_BIT_NOT,	/* ~ */
	OP_BIT_SL,			/* << */
	OP_BIT_SR,			/* >> */
	OP_BIT_XOR,			/* ^ */

	OP_NONE = -1,
};

typedef uint8_t operator_t;

void parse_expr(ParseState* ps);
void parse_assign(ParseState* ps);
void parse_logical_or(ParseState* ps);
void parse_logical_and(ParseState* ps);
void parse_or(ParseState* ps);
void parse_xor(ParseState* ps);
void parse_and(ParseState* ps);
void parse_equilisator(ParseState* ps);
void parse_comparators(ParseState* ps);
void parse_shift(ParseState* ps);
void parse_plusminus(ParseState* ps);
void parse_multdivmod(ParseState* ps);
void parse_unary(ParseState* ps);
void parse_factor(ParseState* ps);

void leaf_int(uint16_t number);
void leaf_call(char* name);
void leaf_assign(char* name);
void leaf_var(char* name);
void leaf_operator(operator_t operator);

#endif /* EXPR_H_ */
