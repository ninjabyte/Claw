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
void parse_logError(ParseState* ps);
uint8_t parse_hasError(ParseState* ps);

void parse_next(ParseState* ps);
uint8_t parse_accept(ParseState* ps, token_t tok);
uint8_t parse_expect(ParseState* ps, token_t tok);

void parse_prog(ParseState* ps);

#endif /* PARSE_H_ */
