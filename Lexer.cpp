
#include "Lexer.hpp"

Lexer::Lexer(const std::string& line)
	: _line(line), _curIndex(0), _curChar(line[0])
{
}

Lexer::~Lexer(void)
{
}

Token	Lexer::lexerGetNextToken(void)
{
	while (this->_curChar != '\0')
	{
		this->lexerSkipWhitespaces();
		if (this->_curChar == '{')
			return (this->getLparenToken());
		if (this->_curChar == '}')
			return (this->getRparenToken());
		if (this->_curChar != '\0')
			return (this->getWordToken());
	}
	return (Token(TOKEN_EOF, "newline"));
}

void	Lexer::lexerSkipWhitespaces(void)
{
	while (isspace(this->_curChar)) {
		this->lexerAdvance();
	}
}

void	Lexer::lexerAdvance(void)
{
	this->_curIndex += 1;
	this->_curChar = this->_line[this->_curIndex];
}

Token	Lexer::getLparenToken(void)
{
	this->lexerAdvance();
	return (Token(TOKEN_LPAREN, "{"));
}

Token	Lexer::getRparenToken(void)
{
	this->lexerAdvance();
	return (Token(TOKEN_RPAREN, "}"));
}

Token	Lexer::getWordToken(void)
{
	std::string	word;

	while (this->_curChar != '\0' && !isspace(this->_curChar) &&
			this->_curChar != '{' && this->_curChar != '}')
	{
		word += this->_curChar;
		this->lexerAdvance();
	}
	return (Token(TOKEN_WORD, word));
}
