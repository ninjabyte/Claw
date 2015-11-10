#include "parseutil.h"
#include "../lex/lex.h"
#include "expr.h"

operator_t parseutil_getOperator(token_t token)
{
	switch(token) {
		case TK_PLUS: return OP_ADD;
		case TK_MINUS: return OP_SUBTRACT;
		case TK_MULTIPLY: return OP_MULTIPLY;
		case TK_DIVIDE: return OP_DIVIDE;
		case TK_MODULUS: return OP_MODULUS;
		case TK_LESS: return OP_LESS;
		case TK_GREATER: return OP_GREATER;
		case TK_LESSEQUALS: return OP_LESSEQUALS;
		case TK_GREATEREQUALS: return OP_GREATEREQUALS;
		case TK_EQUALS: return OP_EQUALS;
		case TK_INEQUALS: return OP_INEQUALS;
		case TK_AND: return OP_AND;
		case TK_OR: return OP_OR;
		case TK_BIT_OR: return OP_BIT_OR;
		case TK_BIT_AND: return OP_BIT_AND;
		case TK_BIT_NOT: return OP_UNARY_BIT_NOT;
		case TK_BIT_SL: return OP_BIT_SL;
		case TK_BIT_SR: return OP_BIT_SR;
		case TK_BIT_XOR: return OP_BIT_XOR;
		default: return OP_NONE;
	}
}
