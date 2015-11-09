#ifndef PARSE_H_
#define PARSE_H_

#include "../lex/lex.h"
#include "../cpl/cpl.h"

typedef struct
{
	LexState* ls; /* lexer state */
	CplState* cs; /* compiler state */
	token_t token; /* the last matched (usefull) token */
	uint8_t error; /* error message, if any */
} ParseState;

void parse_init(ParseState* ps, LexState* ls, CplState* cs);
void parse_parse(ParseState* ps);
void parse_logError(ParseState* ps);

#endif /* PARSE_H_ */
