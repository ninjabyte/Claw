#ifndef LEX_H_
#define LEX_H_

#include <string.h>
#include "token.h"

// queue size for tokens, or the maximum lookahead in tokens
#define QUEUE_SIZE 2

// lexer state struct
typedef struct
{
	const char* src;		// code source pointer
	size_t size;			// the size of the source
	unsigned int current;	// current position in source
	unsigned int line;		// current line in source
	int error;				// error code, if any
	// token queue ring buffer
	Token tok;
} LexState;

void lex_init(LexState* ls, const char* src, size_t size);
void lex_printerr(LexState *ls);
int lex_isFinished(LexState* ls);

void lex_nextToken(LexState* ls);

#endif /* LEX_H_ */
