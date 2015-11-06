#include <string.h>
#include "token.h"
#include "../util/util.h"

const char* token_keywords[] =
{
	"<eoi>", 	"<nl>",

	"<name>", 	"<int>", 	"<string>",	"<ws>",
	"<comment>",

	"block",	"break",	"continue",	"else",
	"elseif",	"end",		"false",	"for",
	"function",	"if",		"return",	"true",
	"var",		"while",

	"+",		"-",		"*",		"/",
	"<",		">",		"<=",		">=",
	"==",		"!=",		"=",		"&&",
	"||",		"|",		"&",		"<<",
	">>",		",",		"(",		")",
	"{",		"}",		"[",		"]"
};

// get string of a token
const char* token_getTokStr(int kw)
{
	if (kw < 0 || kw >= NUM_KEYWORDS)
		return "<none>";
	return token_keywords[kw];
}

// checks if the str string starts with the keyword characters
int token_isKeyWord(const char* str, int kw)
{
	if (kw < TK__FIRST || kw >= NUM_KEYWORDS)
		return 0;
	const char* kwstr = token_getTokStr(kw);
	return util_strncicmp(str, kwstr, strlen(kwstr));
}

// gets the next word token. If str doesnt start with a word, tok.token is set to TK_NONE.
// this token can match a keyword too!
void token_nextName(const char* str, Token* tok)
{
	if (!isLetter(str))
	{
		setTok(tok, str, 0, TK_NONE)
		return;
	}

	size_t i = 1;
	while (!isEOI(str+i) && (isLetter(str+i) || isNumber(str+i)))
		i++;
	setTok(tok, str, i, TK_NAME)
}

// gets the next integer token. If str doesnt start with an int, tok.token is set to TK_NONE.
void token_nextInteger(const char* str, Token* tok)
{
	size_t i = 0;
	while (!isEOI(str+i) && isNumber(str+i))
		i++;
	if (i == 0 || isLetter(str+i))
		setTok(tok, str, 0, TK_NONE)
	else
		setTok(tok, str, i, TK_INT)
}

// gets the next key token. If str doesnt start with a key token, tok.token is set to TK_NONE.
void token_nextKeyToken(const char* str, Token* tok)
{
	int kw = TK_NONE, i;
	size_t len = 0, _tmp;
	for (i=TK__LAST+1; i<NUM_KEYWORDS; i++)
		if (token_isKeyWord(str, i) && (_tmp=strlen(token_getTokStr(i))) > len)
		{
			kw = i;
			len = _tmp;
		}
	setTok(tok, str, len, kw)
}

// gets the next key literal. If str doesnt start with a key literal, tok.token is set to TK_NONE.
void token_nextKeyLiteral(const char* str, Token* tok)
{
	int kw = TK_NONE, i;
	size_t len = 0, ilen;
	for (i=TK__FIRST; i<=TK__LAST; i++)
	{
		ilen = strlen(token_getTokStr(i));
		if (token_isKeyWord(str, i) && !isLetter(str+ilen) && ilen > len)
		{
			kw = i;
			len = ilen;
		}
	}
	setTok(tok, str, len, kw)
}

// gets the next whitespace (length to next non-whitespace token). If str doesnt start with a whitespace, tok.token is set to TK_NONE.
void token_nextWhiteSpace(const char* str, Token* tok)
{
	size_t i = 0;
	while (!isEOI(str+i) && isWhitespace(str+i))
		i++;
	if (i == 0)
		setTok(tok, str, 0, TK_NONE)
	else
		setTok(tok, str, i, TK_WHITESPACE)
}

// gets the next string (quotes, text, closing quotes). If str doesnt start with a string, tok.token is set to TK_NONE.
void token_nextString(const char* str, Token* tok)
{
	if (!isDoubleQuote(str))
	{
		setTok(tok, str, 0, TK_NONE)
		return;
	}

	size_t i = 1;
	while (!isEOI(str+i) && !isDoubleQuote(str+i))
		i++;
	if (isDoubleQuote(str+i))
		i++;
	setTok(tok, str, i, TK_STRING)
}

// gets the next comment. . If str doesnt start with a comment, tok.token is set to TK_NONE.
void token_nextComment(const char* str, Token* tok)
{
	if (!isDot(str))
	{
		setTok(tok, str, 0, TK_NONE)
		return;
	}

	if (isDot(str+1) && isDot(str+2))
	{
		// multiline comment
		size_t i = 3;
		while (!isEOI(str+i) && !(isDot(str+i) && isDot(str+i+1) && isDot(str+i+2)))
			i++;
		if (isDot(str+i) && isDot(str+i+1) && isDot(str+i+2))
			i += 3;
		setTok(tok, str, i, TK_COMMENT)
	}else
	{
		// single line comment
		size_t i = 1;
		while (!isEOI(str+i) && !isNewLine(str+i))
			i++;
		setTok(tok, str, i, TK_COMMENT)
	}
}

// gets the next keyword, TK_NONE if none matched
void token_next(const char* str, Token* tok)
{
	if (isEOI(str))
	{
		setTok(tok, str, 1, TK_EOI)
		return;
	}

	if (isNewLine(str))
	{
		setTok(tok, str, 1, TK_NEWLINE)
		return;
	}

	token_nextComment(str, tok);
	if (tok->token != TK_NONE)
		return;

	token_nextString(str, tok);
	if (tok->token != TK_NONE)
		return;

	token_nextWhiteSpace(str, tok);
	if (tok->token != TK_NONE)
		return;

	token_nextInteger(str, tok);
	if (tok->token != TK_NONE)
		return;

	token_nextKeyToken(str, tok);
	if (tok->token != TK_NONE)
		return;

	token_nextKeyLiteral(str, tok);
	if (tok->token != TK_NONE)
			return;

	token_nextName(str, tok);
}
