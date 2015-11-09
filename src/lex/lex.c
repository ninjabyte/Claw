#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lex.h"
#include "../error/error.h"

const char* lex_keywords[] = {
	"action",	"break",	"continue",	"block",
	"else",		"elseif",	"end",		"false",
	"for",		"function",	"if",		"return",
	"true",		"var", 		"while"
};

#define IS_LETTER(chr) (((chr) >= 'A' && (chr) <= 'Z') || ((chr) >= 'a' && (chr) <= 'z') || ((chr) == '_'))
#define IS_NUMBER(chr) ((chr) >= '0' && (chr) <= '9')
#define IS_HEX(chr) (((chr) >= 'A' && (chr) <= 'F') || ((chr) >= 'a' && (chr) <= 'f') || ((chr) >= '0' && chr <= '9'))
#define HASH(c0, c1) ((c0) << 8 | (c1))

int lex_error(LexState* ls, uint8_t error);

token_t lex_nextLong(LexState*, char, token_t);
char lex_nextEscapeCode(LexState*);
token_t lex_nextChar(LexState*, char);
token_t lex_nextHexNumber(LexState*);
token_t lex_nextNumber(LexState*, char);
token_t lex_nextWord(LexState*, char);

// initialize a lexer
void lex_init(LexState* ls, FILE* fp)
{
	ls->line = 1;
	ls->src = fp;
	ls->in_string = 0;
	ls->in_comment = 0;
	ls->error = 0;
}

// get the keywords' string. doesn't check for out of bounds!
const char* lex_getKeywordString(token_t tok)
{
	return lex_keywords[tok-TOK_FIRST_KW];
}

// set this lexer in an error state
int lex_error(LexState* ls, uint8_t error)
{
	ls->error = error;
	return TK_NONE;
}

// log the error message
void lex_logError(LexState* ls)
{
	error_printmsg(ls->error);
	if (ls->error)
		fprintf(stderr, "at line %d\n", ls->line);
}

// try to read the next token
// if its a name, put it into kf
token_t lex_next(LexState* ls)
{
	int c = fgetc(ls->src);

	if (c == EOF)
	{
		ls->in_comment = 0;
		return TK_EOI;
	}

	if(ls->in_string)
		return lex_nextChar(ls, (char) c);
	else if (ls->in_comment && c != '\n' && c != '\r' && c != 0 && c != EOF){		// there has to be a better way
		ls->kf.character = (char) c;
		return TK_CHARACTER;
	}

	switch(c) {
		case 0:
			ls->in_comment = 0;
			return TK_EOI;
		case '\n':	// line breaks
		case '\r':
			ls->line++;
			ls->in_comment = 0;
			return TK_NEWLINE;
		case ' ': case '\f': case '\t': case '\v': case ';': // whitespace
			return TK_WHITESPACE;
		case '"':
			ls->in_string = 1;
			return TK_QUOTE;
		case '+': return TK_PLUS;
		case '-': return lex_nextLong(ls, c, TK_MINUS);	// TK_MINUS or TK_COMMENT
		case '*': return TK_MULTIPLY;
		case '/': return TK_DIVIDE;
		case '%': return TK_MODULUS;
		case '<': return lex_nextLong(ls, c, TK_LESS);		// TK_LESS, TK_LESSEQUALS or TK_BIT_SL
		case '>': return lex_nextLong(ls, c, TK_GREATER);	// TK_GREATER, TK_GREATEREQUALS or TK_BIT_SR
		case '=': return lex_nextLong(ls, c, TK_ASSIGN);	// TK_ASSIGN or TK_EQUALS
		case '!': return lex_nextLong(ls, c, TK_BIT_NOT);	// TK_BIT_NOT or TK_UNEQUALS
		case '&': return lex_nextLong(ls, c, TK_AND);	// TK_AND or TK_BIT_AND
		case '|': return lex_nextLong(ls, c, TK_OR);	// TK_OR or TK_BIT_OR
		case '^': return TK_BIT_XOR;
		case ',': return TK_COMMA;
		case '(': return TK_BR_OPEN;
		case ')': return TK_BR_CLOSE;
		case '{': return TK_CBR_OPEN;
		case '}': return TK_CBR_CLOSE;
		case '[': return TK_BBR_OPEN;
		case ']': return TK_BBR_CLOSE;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return lex_nextNumber(ls, c);
		default: return lex_nextWord(ls, c);
	}
}

// try to match a token of 2 chars
token_t lex_nextLong(LexState* ls, char c0, token_t defaultTok)
{
	int c1 = fgetc(ls->src);

	switch(HASH(c0, (char) c1)) {
		case HASH('>', '>'): return TK_BIT_SR;
		case HASH('>', '='): return TK_GREATEREQUALS;
		case HASH('<', '<'): return TK_BIT_SL;
		case HASH('<', '='): return TK_LESSEQUALS;
		case HASH('=', '='): return TK_EQUALS;
		case HASH('!', '='): return TK_UNEQUALS;
		case HASH('|', '|'): return TK_OR;
		case HASH('&', '&'): return TK_AND;
		case HASH('-', '-'):
			ls->in_comment = 1;
			return TK_COMMENT;
		default:
			ungetc(c1, ls->src);
			return defaultTok;
	}
}

// get the actual char of an escape code
char lex_nextEscapeCode(LexState* ls)
{
	int c1 = fgetc(ls->src);
	switch (c1){
		case EOF:
			ungetc(c1, ls->src);
			return -1;
		case 'a': return '\a';
		case 'b': return '\b';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';
		case 'v': return '\v';
		case '\\': return '\\';
		case '\'': return '\'';
		case '"': return '"';
		case '?': return '?';
		case '\r':
		case '\n': return ' ';
		default: return '\\';
	}
}

// try to parse the next char
token_t lex_nextChar(LexState* ls, char c0)
{
	switch(c0){
		case 0:
		case EOF:
			ls->kf.character = 0;
			ls->error = ERR_UNEXPECTED_EOI;
			return TK_EOI;
		case '"':
			ls->in_string = 0;
			return TK_QUOTE;
		case '\n':
			ls->line++;
			return lex_nextChar(ls, fgetc(ls->src));
		case '\\':	// escape code
			ls->kf.character = lex_nextEscapeCode(ls);
			if(ls->kf.character == -1)
				return lex_error(ls, ERR_INVALID_ESCAPE);
			return TK_CHARACTER;
		case '#': // hexadecimal number
			ls->kf.number = lex_nextHexNumber(ls);
			return TK_NUMBER;
		default:
			ls->kf.character = c0;
			return TK_CHARACTER;
	}
}

// try to match an html style hexadecimal number
token_t lex_nextHexNumber(LexState* ls)
{
	uint16_t number = 0, i;
	int c;

	for (i=0; i<4; i++) {
		c = fgetc(ls->src);

		if (IS_HEX(c)) {
			number = number << 4;
			number |= c;
		} else {
			ungetc(c, ls->src);
			break;
		}
	}

	ls->kf.number = number;
	return TK_NUMBER;
}

// try to match a number
token_t lex_nextNumber(LexState* ls, char c0)
{
	uint16_t number = 0;
	int cx = c0;

	uint8_t i;
	for (i=0; i<7; i++) {
		if (IS_NUMBER(cx)) {
			number *= 10;
			number += cx - '0';
			cx = fgetc(ls->src);
		} else {
			ungetc(cx, ls->src);
			break;
		}
	}

	ls->kf.number = number;
	return TK_NUMBER;
}

// try to match the next word. Returns a keyword if the next word is a keyword
token_t lex_nextWord(LexState* ls, char c0)
{
	int cx = c0;

	for(int i=0; i<17; i++)
		ls->kf.name[i] = 0;

	if (!IS_LETTER(cx)) {
		ungetc(cx, ls->src);
		return lex_error(ls, ERR_UNEXPECTED_INPUT);
	}

	ls->kf.name[0] = cx;
	uint8_t i;
	for (i=1; i<16; i++) {
		cx = fgetc(ls->src);
		if (!(IS_LETTER(cx) || IS_NUMBER(cx)) || cx == EOF) {
			ungetc(cx, ls->src);
			i--;
			break;
		}
		ls->kf.name[i] = cx;
	}

	ls->kf.name[++i] = 0;
	int kw;
	for (kw=TOK_FIRST_KW; kw<=TOK_LAST_KW; kw++)
		if (strlen(lex_getKeywordString(kw)) == i && strncmp(ls->kf.name, lex_getKeywordString(kw), i) == 0)
			return kw;

	return TK_NAME;
}

void lex_debugPrintToken(LexState* ls, token_t tok)
{
	switch(tok) {
		case TK_NAME:
			printf("name: %s", ls->kf.name);
			break;
		case TK_CHARACTER:
			if (ls->kf.character > 32) {
				printf("char: %c", ls->kf.character);
			} else if(ls->kf.character == 32) {
				printf("char: (space)");
			} else
				printf("char: 0x%02hhX", ls->kf.character);
			break;
		case TK_NUMBER:
			printf("number: %d", ls->kf.number);
			break;
		default:
			if(tok >= TOK_FIRST_KW && tok <= TOK_LAST_KW)
				printf("keyword: %s", lex_getKeywordString(tok));
			else
				printf("token: %d", tok);
			break;
	}
	printf("\n");
}
