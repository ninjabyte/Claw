#ifndef LEX_H_
#define LEX_H_

#include <stdio.h>
#include <stdint.h>

enum Keyword
{
	TK_EOI,				// end of input
	TK_NEWLINE,			// new line
	TK_WHITESPACE,		// whitespace

	TK_NAME,			// a name. Maximum length of 16 characters

	// keywords
	TK_BREAK,			// break
	TK_CONTINUE,		// continue
	TK_BLOCK,			// block
	TK_ELSE,			// else
	TK_ELSEIF,			// elseif
	TK_END,				// end
	TK_FALSE,			// false
	TK_FOR,				// for
	TK_FUNCTON,			// function
	TK_IF,				// if
	TK_RETURN,			// return
	TK_TRUE,			// true
	TK_VAR,				// var
	TK_WHILE,			// while

	// key tokens
	TK_PLUS,			// +
	TK_MINUS,			// -
	TK_MULTIPLY,		// *
	TK_DIVIDE,			// /
	TK_MODULUS,			// %
	TK_LESS,			// <
	TK_GREATER,			// >
	TK_LESSEQUALS,		// <=
	TK_GREATEREQUALS,	// >=
	TK_EQUALS,			// ==
	TK_UNEQUALS,		// !=
	TK_ASSIGN,			// =
	TK_AND,				// &&
	TK_OR,				// ||
	TK_BIT_OR,			// |
	TK_BIT_AND,			// &
	TK_BIT_NOT,			// !
	TK_BIT_SL,			// <<
	TK_BIT_SR,			// >>
	TK_BIT_XOR,			// ^
	TK_COMMA,			// ,
	TK_BR_OPEN,			// (
	TK_BR_CLOSE,		// )
	TK_CBR_OPEN,		// {
	TK_CBR_CLOSE,		// }
	TK_BBR_OPEN,		// [
	TK_BBR_CLOSE,		// ]
	TK_COMMENT,			// --
	TK_NUMBER,			// 0-9
	TK_QUOTE,			// "
	NUM_KEYWORDS,
	TK_NONE = -1
};

// the first string kw
#define TOK_FIRST_KW TK_BREAK
// the last string kw
#define TOK_LAST_KW	TK_WHILE

// lexer state
typedef struct
{
	FILE* src;	// the source file
	int line;	// the current line number
	int last_token; // last parsed token
	char last_chr; // last character
} LexState;

// to store additional info about the keyword
typedef struct
{
	char name[17];
	int16_t number;
} KeywordInfo;

void lex_init(LexState* ls, FILE* fp);
int lex_next(LexState* ls, KeywordInfo *kf);
int lex_test(char* file);

#endif /* LEX_H_ */
