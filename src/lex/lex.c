#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lex.h"
#include "../error/error.h"

const char* lex_keywords[] =
{
	"break",	"continue",	"block",	"else",
	"elseif",	"end",		"false",	"for",
	"function",	"if",		"return",	"true",
	"var", 		"while"
};

// the alphabet of characters allowed in a name
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
#define IS_LETTER(chr) ((chr) != 0 && strchr(ALPHABET, chr) != NULL)
#define IS_NUMBER(chr) (chr >= '0' && chr <= '9')
#define IS_VALID_LETTER_NAME(chr) ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || (chr == '_'))
#define HASH(c0, c1) ((c0) << 8 | (c1))

int lex_nextLong(LexState* ls, char c0, int defaultTok);
int lex_nextNumber(LexState* ls, char c0);
int lex_nextWord(LexState* ls, char c0);

// initialize a lexer
void lex_init(LexState* ls, FILE* fp)
{
	ls->line = 0;
	ls->src = fp;
	ls->last_token = TK_NONE;
}

// try to read the next token
// if its a name, put it into kf
int lex_next(LexState* ls)
{
	int c = fgetc(ls->src);

	switch(c)
	{
		case 0:
		case EOF:
			return TK_EOI;
		case '\n':	// line breaks
		case '\r':
			ls->line++;
			return TK_NEWLINE;
		case ' ': case '\f': case '\t': case '\v': case ';': // whitespace
			return TK_WHITESPACE;
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
		case '"': return TK_QUOTE;
		default: return lex_nextWord(ls, c);
	}
	return TK_NONE;
}

// try to match a token of 2 chars
int lex_nextLong(LexState* ls, char c0, int defaultTok)
{
	int c1 = fgetc(ls->src);

	switch(HASH(c0, (char) c1))
	{
		case HASH('>', '>'): return TK_BIT_SR;
		case HASH('>', '='): return TK_GREATEREQUALS;
		case HASH('<', '<'): return TK_BIT_SL;
		case HASH('<', '='): return TK_LESSEQUALS;
		case HASH('=', '='): return TK_EQUALS;
		case HASH('!', '='): return TK_UNEQUALS;
		case HASH('|', '|'): return TK_OR;
		case HASH('&', '&'): return TK_AND;
		case HASH('-', '-'): return TK_COMMENT;
		default:
			ungetc(c1, ls->src);
			return defaultTok;
	}
}

// try to match a number
int lex_nextNumber(LexState* ls, char c0)
{
	uint16_t number = 0;
	uint8_t i = 0;
	char cx = c0;

	for ( ; i<7; i++)
	{
		if (IS_NUMBER(cx))
		{
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

// try t match the next word. Returns a keyword if the next word is a keyword
int lex_nextWord(LexState* ls, char c0)
{
	char name[17];
	int cx = c0;

	if (!IS_LETTER(cx))
	{
		ungetc(c0, ls->src);
		return TK_NONE;
	}

	uint8_t i;
	for (i=1; i<16; i++)
	{
		if (!IS_LETTER(cx) || cx == EOF)
		{
			break;
		}
		name[i] = (char) cx;
		cx = fgetc(ls->src);
	}
	name[++i] = 0;
	int j;
	for (j=TOK_FIRST_KW; j<=TOK_LAST_KW; j++)
		if (strlen(lex_keywords[j-TOK_FIRST_KW]) == i && strncmp(name, lex_keywords[j-TOK_FIRST_KW], i) == 0)
			return j;

	memcpy(ls->kf.name, name, i+1);
	return TK_NAME;
}
