
#include "Lexer.hpp"
#include <cctype>

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
		lexerSkipWhitespaces();
		if (this->_curChar == '{')
			...;
		else if (this->_curChar == '}')
			...;
		else
			collect_current
	}
	return (Token(TOKEN_EOF, "newline"));
}
int isspace ( int c );

void	Lexer::lexerSkipWhitespaces(void)
{
	while (isspace(this->_curChar) == true)
		lexerAdvance();
}

void	Lexer::lexerAdvance(void)
{
	this->_curIndex++;
	this->_curChar = this->_line[this->_curIndex];
}
