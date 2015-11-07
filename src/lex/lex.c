#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "../error/error.h"

const char* lex_keywords[] =
{
	"break",	"continue",	"block",	"else",
	"elseif",	"end",		"false",	"for",
	"function",	"if",		"return",	"true",
	"var", "while"
};

// the alphabet of characters allowed in a name
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
#define isLetter(chr) (chr != 0 && strchr(ALPHABET, chr) != NULL)

// initialize a lexer
void lex_init(LexState* ls, FILE* fp)
{
	ls->line = 0;
	ls->src = fp;
}

// try to match a token of 2 chars
int lex_nextLongToken(LexState* ls, char c0, char c1)
{
	return 0;
}

// try to read the next token
// if its a name, put it into kf
int lex_next(LexState* ls)
{
	int c = fgetc(ls->src), c1;

	switch(c) {
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
		case '-':	// TK_MINUS or TK_COMMENT
			return TK_NONE;
		case '*': return TK_MULTIPLY;
		case '/': return TK_DIVIDE;
		case '%': return TK_MODULUS;
		case '<':	// TK_LESS, TK_LESSEQUALS or TK_BIT_SL
			return TK_NONE;
		case '>':	// TK_GREATER, TK_GREATEREQUALS or TK_BIT_SR
			c1 = fgetc(ls->src);
			switch(c1)
			{
			case '>': return TK_BIT_SR;
			case '=': return TK_GREATEREQUALS;
			}
			ungetc(c1, ls->src);
			return TK_GREATER;
		case '=':	// TK_ASSIGN or TK_EQUALS
			c1 = fgetc(ls->src);
			if (c1 == '=')
				return TK_EQUALS;
			ungetc(c1, ls->src);
			return TK_ASSIGN;
		case '!':	// TK_BIT_NOT or TK_UNEQUALS
			c1 = fgetc(ls->src);
			if (c1 == '=')
				return TK_UNEQUALS ;
			ungetc(c1, ls->src);
			return TK_BIT_NOT;
		case '&':	// TK_AND or TK_BIT_AND
			c1 = fgetc(ls->src);
			if (c1 == '&')
				return TK_AND;
			ungetc(c1, ls->src);
			return TK_BIT_AND;
		case '|':	// TK_OR or TK_BIT_OR
			c1 = fgetc(ls->src);
			if (c1 == '|')
				return TK_OR;
			ungetc(c1, ls->src);
			return TK_BIT_OR;
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
			return TK_NONE;
		case '"':
			return TK_QUOTE;
		default:
			{
				char name[17];
				int i;
				for (i=0; i<16; i++)
				{
					name[i] = (char) c;
					c = fgetc(ls->src);
					if (c == EOF)
						break;
					if (!isLetter(c))
					{
						ungetc(c, ls->src);
						break;
					}
				}
				name[++i] = 0;
				int j;
				for (j=TOK_FIRST_KW; j<=TOK_LAST_KW; j++)
					if (strlen(lex_keywords[j-TOK_FIRST_KW]) == i && strncmp(name, lex_keywords[j-TOK_FIRST_KW], i) == 0)
						return j;

				memcpy(ls->kf.name, name, i+1);
				return TK_NAME;
		}
	}
	return TK_NONE;
}

/*
int lex_require_multiple_chars(LexState* ls, KeywordInfo *kf, char chr)
{
	char digits[7];
	int digit_ptr = 0;
	char last_chr = chr;

	while(1) {
		int c = fgetc(ls->src);

		switch(last_chr) {
			case '-':
				if (c == '-')
					return TK_COMMENT);
				ungetc(c, ls->src);
				return TK_MINUS);
			case '<':
				switch(c) {
					case '<': return TK_BIT_SL);
					case '=': return TK_LESSEQUALS);
				}
				ungetc(c, ls->src);
					return TK_LESS);
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if(c >= '0' && c <= '9') {
					if(digit_ptr < 7) {
						digits[digit_ptr++] = c;
						last_chr = c;
						continue;
					} else
						return TK_NONE; // ERROR - OVERFLOW!!!
				} else {
					ungetc(c, ls->src);
					kf->number = atoi(digits);
					return TK_NUMBER);
				}
		}
	}
}*/
