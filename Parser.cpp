
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
	while (this->_curToken.type != TOKEN_EOF)
	{
		while (this->_curToken.type == TOKEN_EOL) {
			this->expectedToken(TOKEN_EOL);
		}
		if (this->_curToken.value == "server") {
			this->parserParseServer();
		}
		else if (this->_curToken.type != TOKEN_EOF) {
			throw SyntaxError(this->_curToken.value);
		}
	}
	// CHECK if exist at least one server or not [ CHECK AST ] ...
}

void	Parser::parserParseServer(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	while (this->_curToken.type != TOKEN_RPAREN)
	{
		while (this->_curToken.type == TOKEN_EOL) {
			this->expectedToken(TOKEN_EOL);
		}
		if (this->_curToken.type == TOKEN_RPAREN)
			break ;

		if (this->_curToken.value == "listen")
			this->parserParseListen();
		else if (this->_curToken.value == "server_name")
			this->parserParseServerName();
		else if (this->_curToken.value == "error_page")
			this->parserParseErrorPage();
		else if (this->_curToken.value == "limit_client_body_size")
			this->parserParseLimitSize();
		else if (this->_curToken.value == "accepted_methods")
			this->parserParseAcceptedMethods();
		else if (this->_curToken.value == "root")
			this->parserParseRoot();
		else if (this->_curToken.value == "index")
			this->parserParseIndex();
		else if (this->_curToken.value == "autoindex")
			this->parserParseAutoIndex();
		else if (this->_curToken.value == "location")
			this->parserParseLocation();
		else
			throw SyntaxError(this->_curToken.value);
	}
	this->expectedToken(TOKEN_RPAREN);
	if (this->_curToken.type != TOKEN_EOL && this->_curToken.type != TOKEN_EOF)
		throw SyntaxError(this->_curToken.value);
	if (this->_curToken.type != TOKEN_EOF)
		this->_curToken = this->_lexer.lexerGetNextToken();
	// CHECK if listen directive exist ...
}

void	Parser::parserParseLocation(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	while (this->_curToken.type != TOKEN_RPAREN)
	{
		while (this->_curToken.type == TOKEN_EOL) {
			this->expectedToken(TOKEN_EOL);
		}
		if (this->_curToken.type == TOKEN_RPAREN)
			break ;

		if (this->_curToken.value == "error_page")
			this->parserParseErrorPage();
		else if (this->_curToken.value == "limit_client_body_size")
			this->parserParseLimitSize();
		else if (this->_curToken.value == "accepted_methods")
			this->parserParseAcceptedMethods();
		else if (this->_curToken.value == "root")
			this->parserParseRoot();
		else if (this->_curToken.value == "index")
			this->parserParseIndex();
		else if (this->_curToken.value == "autoindex")
			this->parserParseAutoIndex();
		else
			throw SyntaxError(this->_curToken.value);
	}
	this->expectedToken(TOKEN_RPAREN);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseListen(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	for (size_t i = 0; i < 2; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseServerName(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	while (this->_curToken.type == TOKEN_WORD) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseErrorPage(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	for (size_t i = 0; i < 2; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseLimitSize(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAcceptedMethods(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	for (size_t i = 0; i < 2 && this->_curToken.type == TOKEN_WORD; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseRoot(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseIndex(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	while (this->_curToken.type == TOKEN_WORD) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAutoIndex(void)
{
	this->expectedToken(TOKEN_WORD); // ...

	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::expectedToken(TokenType type)
{
	if (this->_curToken.type != type) {
		throw SyntaxError(this->_curToken.value);
	}
	// TODO: ADD data to AST (TOKEN_WORD) ...
	this->_curToken = this->_lexer.lexerGetNextToken();
}
