#ifndef LEX_H_
#define LEX_H_

#include <stdio.h>
#include <stdint.h>

enum Keyword
{
	TK_EOI,				// end of input (0)
	TK_NEWLINE,			// new line
	TK_WHITESPACE,		// whitespace

	TK_NAME,			// a name. Maximum length of 16 characters
	TK_CHARACTER,		// a character in a string

	// keywords
	TK_BREAK,			// break
	TK_CONTINUE,		// continue (5)
	TK_BLOCK,			// block
	TK_ELSE,			// else
	TK_ELSEIF,			// elseif
	TK_END,				// end
	TK_FALSE,			// false (10)
	TK_FOR,				// for
	TK_FUNCTON,			// function
	TK_IF,				// if
	TK_RETURN,			// return
	TK_TRUE,			// true (15)
	TK_VAR,				// var
	TK_WHILE,			// while

	// key tokens
	TK_PLUS,			// +
	TK_MINUS,			// -
	TK_MULTIPLY,		// * (20)
	TK_DIVIDE,			// /
	TK_MODULUS,			// %
	TK_LESS,			// <
	TK_GREATER,			// >
	TK_LESSEQUALS,		// <= (25)
	TK_GREATEREQUALS,	// >=
	TK_EQUALS,			// ==
	TK_UNEQUALS,		// !=
	TK_ASSIGN,			// =
	TK_AND,				// && (30)
	TK_OR,				// ||
	TK_BIT_OR,			// |
	TK_BIT_AND,			// &
	TK_BIT_NOT,			// !
	TK_BIT_SL,			// << (35)
	TK_BIT_SR,			// >>
	TK_BIT_XOR,			// ^
	TK_COMMA,			// ,
	TK_BR_OPEN,			// (
	TK_BR_CLOSE,		// ) (40)
	TK_CBR_OPEN,		// {
	TK_CBR_CLOSE,		// }
	TK_BBR_OPEN,		// [
	TK_BBR_CLOSE,		// ]
	TK_COMMENT,			// -- (45)
	TK_NUMBER,			// 0-9
	TK_QUOTE,			// "
	NUM_KEYWORDS,
	TK_NONE = -1
};

// the first string kw
#define TOK_FIRST_KW TK_BREAK
// the last string kw
#define TOK_LAST_KW	TK_WHILE

// to store additional info about the keyword
typedef struct
{
	char name[17];
	uint16_t number;
	char character;
} KeywordInfo;

typedef struct
{
} KeywordBuffer;

// lexer state
typedef struct
{
	FILE* src;	// the source file
	int line;	// the current line number
	int last_token; // last parsed token
	int in_comment; // is in comment
	int in_string; // is in string
	KeywordBuffer kb; // reserved
	KeywordInfo kf; // detailed info about the keyword if available
} LexState;

void lex_init(LexState* ls, FILE* fp);
const char* lex_getKeywordString(int tok);
int lex_next(LexState* ls);

#endif /* LEX_H_ */
