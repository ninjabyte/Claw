#include <stdio.h>
#include <stdint.h>
#include "leaf.h"
#include "parse.h"
#include "../error/error.h"
#include "../lex/lex.h"
#include "../cpl/cpl.h"

/* integer leaf */
void leaf_int(ParseState* ps)
{
	if (parse_hasError(ps) || ps->token != TK_NUMBER)
		return;
	printf("%d", ps->ls->kf.number);
}
