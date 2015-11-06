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
	TK_BLOCK,			// block
	TK_BREAK,			// break
	TK_CONTINUE,		// continue
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
	TK_BIT_SL,			// <<
	TK_BIT_SR,			// >>
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
#define TK__FIRST TK_BREAK
// the last key literal.
#define TK__LAST TK_WHILE

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

// eoi character
#define EOI ((char) 0)
// newline character
#define NEWLINE '\n'
// double quote character
#define DOUBLE_QUOTE '"'
// dot character
#define DOT '.'

// allowed characters
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
// allowed numbers
#define NUMBERS "0123456789"
// whitespace characters
#define WHITESPACE " \t\r"

// initialize a token _tok with values _tok.seq = _seq, _tok.seqlen = _len and _tok.keyword = _kw
#define setTok(_tok, _seq, _len, _kw) {(_tok)->seq = _seq; (_tok)->seqlen = _len; (_tok)->token = _kw;}
// check if the string starts with an end of input character
#define isEOI(str) ((str)[0] == EOI)
// check if the string starts with a newline character
#define isNewLine(str) ((str)[0] == NEWLINE)
// check if the string starts with a double quote
#define isDoubleQuote(str) ((str)[0] == DOUBLE_QUOTE)
// check if the string starts with a dot
#define isDot(str) ((str)[0] == DOT)
// check if the string starts with a letter character
#define isLetter(str) ((str)[0] != 0 && strchr(ALPHABET, (str)[0]) != NULL)
// check if the string starts with a numer character
#define isNumber(str) ((str)[0] != 0 && strchr(NUMBERS, (str)[0]) != NULL)
// check if the string starts with a whitespace
#define isWhitespace(str) ((str)[0] != 0 && strchr(WHITESPACE, (str)[0]) != NULL)

#endif /* TOKEN_H_ */
