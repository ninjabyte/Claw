#ifndef PARSEUTIL_H_
#define PARSEUTIL_H_

#include "../lex/lex.h"
#include "expr.h"

operator_t parseutil_getOperator(token_t token);

#endif /* PARSEUTIL_H_ */
