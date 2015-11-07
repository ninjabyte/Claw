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

#define REQUIRE_NEXT_CHAR() last_chr = c; continue;
#define RETURN_TOKEN(tok) ls->last_token = tok; return tok;

// try to read the next token
// if its a name, put it into kf
int lex_next(LexState* ls, KeywordInfo *kf)
{
	char digits[7];
	int digit_ptr = 0;
	char last_chr = 0;

	while(1) {
		int c = fgetc(ls->src), c1;

		switch(ls->last_chr) {
		case '-':
			if (c == '-')
				RETURN_TOKEN(TK_COMMENT);
			ungetc(c, ls->src);
			RETURN_TOKEN(TK_MINUS);
		case '<':
			switch(c) {
				case '<': RETURN_TOKEN(TK_BIT_SL);
				case '=': RETURN_TOKEN(TK_LESSEQUALS);
			}
			ungetc(c, ls->src);
			RETURN_TOKEN(TK_LESS);
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if(c >= '0' && c <= '9') {
				if(digit_ptr < 7) {
					digits[digit_ptr++] = c;
					REQUIRE_NEXT_CHAR();
				} else {
					return TK_NONE; // ERROR - OVERFLOW!!!
				}
			} else {
				ungetc(c, ls->src);
				kf->number = atoi(digits);
				RETURN_TOKEN(TK_NUMBER);
			}
		}

		switch(c)
		{
		case 0:
		case EOF:
			RETURN_TOKEN(TK_EOI);
		case '\n':	// line breaks
		case '\r':
			ls->line++;
			RETURN_TOKEN(TK_NEWLINE);
		case ' ': case '\f': case '\t': case '\v': case ';': // whitespace
			RETURN_TOKEN(TK_WHITESPACE);
		case '+': RETURN_TOKEN(TK_PLUS);
		case '-':	// TK_MINUS or TK_COMMENT
			REQUIRE_NEXT_TOKEN();
		case '*': RETURN_TOKEN(TK_MULTIPLY);
		case '/': RETURN_TOKEN(TK_DIVIDE);
		case '%': RETURN_TOKEN(TK_MODULUS);
		case '<':	// TK_LESS, TK_LESSEQUALS or TK_BIT_SL
			REQUIRE_NEXT_CHAR();
		case '>':	// TK_GREATER, TK_GREATEREQUALS or TK_BIT_SR
			c1 = fgetc(ls->src);
			switch(c1)
			{
			case '>': RETURN_TOKEN(TK_BIT_SR);
			case '=': RETURN_TOKEN(TK_GREATEREQUALS);
			}
			ungetc(c1, ls->src);
			RETURN_TOKEN(TK_GREATER);
		case '=':	// TK_ASSIGN or TK_EQUALS
			c1 = fgetc(ls->src);
			if (c1 == '=')
				RETURN_TOKEN(TK_EQUALS);
			ungetc(c1, ls->src);
			RETURN_TOKEN(TK_ASSIGN);
		case '!':	// TK_BIT_NOT or TK_UNEQUALS
			c1 = fgetc(ls->src);
			if (c1 == '=')
				RETURN_TOKEN(TK_UNEQUALS);
			ungetc(c1, ls->src);
			RETURN_TOKEN(TK_BIT_NOT);
		case '&':	// TK_AND or TK_BIT_AND
			c1 = fgetc(ls->src);
			if (c1 == '&')
				RETURN_TOKEN(TK_AND);
			ungetc(c1, ls->src);
			RETURN_TOKEN(TK_BIT_AND);
		case '|':	// TK_OR or TK_BIT_OR
			c1 = fgetc(ls->src);
			if (c1 == '|')
				RETURN_TOKEN(TK_OR);
			ungetc(c1, ls->src);
			RETURN_TOKEN(TK_BIT_OR);
		case '^': RETURN_TOKEN(TK_BIT_XOR);
		case ',': RETURN_TOKEN(TK_COMMA);
		case '(': RETURN_TOKEN(TK_BR_OPEN);
		case ')': RETURN_TOKEN(TK_BR_CLOSE);
		case '{': RETURN_TOKEN(TK_CBR_OPEN);
		case '}': RETURN_TOKEN(TK_CBR_CLOSE);
		case '[': RETURN_TOKEN(TK_BBR_OPEN);
		case ']': RETURN_TOKEN(TK_BBR_CLOSE);
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			REQUIRE_NEXT_CHAR(c);
		case '"':
			RETURN_TOKEN(TK_QUOTE);
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
						RETURN_TOKEN(j);

				memcpy(kf->name, name, i+1);
				RETURN_TOKEN(TK_NAME);
			}
		}
	}
	RETURN_TOKEN(TK_NONE);
}
