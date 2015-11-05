#ifndef TOKEN_H_
#define TOKEN_H_

#include <string.h>

// every keyword/token in the language
enum TokenType
{
	TK_EOI,				// end of input
	TK_NEWLINE,			// newline

	TK_NAME,			// a name of a variable or label
	TK_INT,				// a number constant
	TK_STRING,			// a string constant
	TK_WHITESPACE,		// useless spaces
	TK_COMMENT,			// a comment

	// key literals
	TK_TRUE,			// true
	TK_FALSE,			// false
	TK_LOG_AND,			// and
	TK_LOG_OR,			// or
	TK_LABEL,			// lbl
	TK_GOTO,			// goto
	TK_RETURN,			// return
	TK_IF,				// if
	TK_ELSE,			// else
	TK_ELSEIF,			// elseif
	TK_FOR,				// for
	TK_WHILE,			// while
	TK_REPEAT,			// repeat
	TK_END,				// end

	// key tokens
	TK_PLUS,			// +
	TK_MINUS,			// -
	TK_STAR,			// *
	TK_SLASH,			// /
	TK_LESS,			// <
	TK_GREATER,			// >
	TK_LESSEQUALS,		// <=
	TK_GREATEREQUALS,	// >=
	TK_EQUALS,			// =
	TK_NOTEQUALS,		// !=
	TK_ARROW,			// ->
	TK_BIT_AND,			// &
	TK_BIT_OR,			// |
	TK_BIT_XOR,			// ^^
	TK_HAT,				// ^
	TK_COMMA,			// ,
	TK_BR_OPEN,			// (
	TK_BR_CLOSE,		// )
	TK_CBR_OPEN,		// {
	TK_CBR_CLOSE,		// }
	TK_BBR_OPEN,		// [
	TK_BBR_CLOSE,		// ]
	NUM_KEYWORDS,
	TK_NONE = -1
};

// the first key literal.
#define TK__FIRST TK_TRUE
// the last key literal.
#define TK__LAST TK_END

// token struct
typedef struct
{
	const char* seq;		// the position in the source
	size_t seqlen;			// the length of the sequence
	int token;				// the actual token, see the "TokenType" enum
} Token;

const char* token_getTokStr(int kw);

int token_isKeyWord(const char* src, int kw);

void token_nextWord(const char* src, Token* tok);
void token_nextInteger(const char* src, Token* tok);
void token_nextKeyToken(const char* src, Token* tok);
void token_nextKeyLiteral(const char* src, Token* tok);
void token_nextString(const char* src, Token* tok);
void token_nextComment(const char* str, Token* tok);

void token_next(const char* src, Token* tok);

#endif /* TOKEN_H_ */
