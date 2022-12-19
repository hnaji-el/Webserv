
#include "Parser.hpp"

/*
 * Constructors && Destructor
 */

Parser::Parser(const std::string& fileName)
	: _lexer(fileName)
{
	this->_curToken = this->_lexer.lexerGetNextToken();
}

Parser::~Parser(void)
{
}

/*
 * Member functions
 */

void	Parser::parserParse(void)
{
	if (this->_curToken.value == "listen") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseListen();
	}
}

void	Parser::parserParseServer(void)
{
}

void	Parser::parserParseLocation(void)
{
}

void	Parser::parserParseListen(void)
{
	size_t	i = 0;

	for (;i < 2; i++)
	{
		if (this->_curToken.type != TOKEN_WORD)
			break ;
		this->_curToken = this->_lexer.lexerGetNextToken();
	}

	if (i != 2 || this->_curToken.type != TOKEN_EOL) {
		std::cerr << "syntax error near unexpected token `";
		std::cerr << this->_curToken.value << "'" << std::endl;
	}
}

void	Parser::parserParseServerName(void)
{
}

void	Parser::parserParseErrorPage(void)
{
}

void	Parser::parserParseLimitSize(void)
{
}

void	Parser::parserParseAcceptedMethods(void)
{
}

void	Parser::parserParseRoot(void)
{
}

void	Parser::parserParseAutoindex(void)
{
}

void	Parser::parserParseIndex(void)
{
}

#if 0
void	Parser::parserParse(void)
{
	while (this->_curToken.type != TOKEN_EOF)
	{
		std::cout << this->_curToken.type << "|";
		std::cout << this->_curToken.value << "|";
		std::cout << std::endl;
		this->_curToken = this->_lexer.lexerGetNextToken();
	}

	std::cout << this->_curToken.type << "|";
	std::cout << this->_curToken.value << "|";
	std::cout << std::endl;

	return ;
}
#endif
