
#include "Parser.hpp"

/*
 * Constructors && Destructor
 */

Parser::Parser(const std::string& fileName)
	: _lexer(fileName)
{
	this->_curToken = this->_lexer.lexerGetNextToken();
	this->_prevToken = this->_curToken;

	this->fillServerTable();
	this->fillLocationTable();
}

Parser::~Parser(void)
{
}

/*
 * member functions for dispatching
 */

void	Parser::fillServerTable(void)
{
	this->_serverTable["listen"] = &Parser::parserParseListen;
	this->_serverTable["server_name"] = &Parser::parserParseServerName;
	this->_serverTable["error_page"] = &Parser::parserParseErrorPage;
	this->_serverTable["limit_client_body_size"] = &Parser::parserParseLimitSize;
	this->_serverTable["accepted_methods"] = &Parser::parserParseAcceptedMethods;
	this->_serverTable["root"] = &Parser::parserParseRoot;
	this->_serverTable["index"] = &Parser::parserParseIndex;
	this->_serverTable["autoindex"] = &Parser::parserParseAutoIndex;
	this->_serverTable["location"] = &Parser::parserParseLocation;
}

void	Parser::fillLocationTable(void)
{
	this->_locationTable["error_page"] = &Parser::parserParseErrorPage;
	this->_locationTable["limit_client_body_size"] = &Parser::parserParseLimitSize;
	this->_locationTable["accepted_methods"] = &Parser::parserParseAcceptedMethods;
	this->_locationTable["root"] = &Parser::parserParseRoot;
	this->_locationTable["index"] = &Parser::parserParseIndex;
	this->_locationTable["autoindex"] = &Parser::parserParseAutoIndex;
}

/*
 * Member functions
 */

void	Parser::parserParse(void)
{
	while (this->_curToken.type != TOKEN_EOF)
	{
		while (this->_curToken.type == TOKEN_EOL)
			this->expectedToken(TOKEN_EOL);
		if (this->_curToken.value == "server")
		{
			this->expectedToken(TOKEN_WORD);
			this->parserParseServer();
		}
		else if (this->_curToken.type != TOKEN_EOF)
			throw SyntaxError(this->_curToken.value);
	}
	// CHECK if exist at least one server or not [ CHECK AST ] ...
}

void	Parser::parserParseServer(void)
{
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	while (this->_curToken.type != TOKEN_RPAREN)
	{
		while (this->_curToken.type == TOKEN_EOL)
			this->expectedToken(TOKEN_EOL);
		if (this->_curToken.type == TOKEN_RPAREN)
			break ;
		Map::iterator	iter = this->_serverTable.find(this->_curToken.value);
		if (iter == this->_serverTable.end())
			throw SyntaxError(this->_curToken.value);
		this->expectedToken(TOKEN_WORD);
		(this->*(iter->second))();
	}

	this->expectedToken(TOKEN_RPAREN);
	if (this->_curToken.type != TOKEN_EOL && this->_curToken.type != TOKEN_EOF)
		throw SyntaxError(this->_curToken.value);
	if (this->_curToken.type == TOKEN_EOL)
		this->expectedToken(TOKEN_EOL);
	// CHECK if listen directive exist ...
}

void	Parser::parserParseLocation(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	while (this->_curToken.type != TOKEN_RPAREN)
	{
		while (this->_curToken.type == TOKEN_EOL)
			this->expectedToken(TOKEN_EOL);
		if (this->_curToken.type == TOKEN_RPAREN)
			break ;
		Map::iterator	iter = this->_serverTable.find(this->_curToken.value);
		if (iter == this->_serverTable.end())
			throw SyntaxError(this->_curToken.value);
		this->expectedToken(TOKEN_WORD);
		(this->*(iter->second))();
	}
	this->expectedToken(TOKEN_RPAREN);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseListen(void)
{
	for (size_t i = 0; i < 2; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseServerName(void)
{
	this->expectedToken(TOKEN_WORD);
	while (this->_curToken.type == TOKEN_WORD) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseErrorPage(void)
{
	for (size_t i = 0; i < 2; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseLimitSize(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAcceptedMethods(void)
{
	this->expectedToken(TOKEN_WORD);
	for (size_t i = 0; i < 2 && this->_curToken.type == TOKEN_WORD; i++) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseRoot(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseIndex(void)
{
	this->expectedToken(TOKEN_WORD);
	while (this->_curToken.type == TOKEN_WORD) {
		this->expectedToken(TOKEN_WORD);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAutoIndex(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_EOL);
}

void	Parser::expectedToken(TokenType type)
{
	if (this->_curToken.type != type)
		throw SyntaxError(this->_curToken.value);

	this->_prevToken = this->_curToken;
	this->_curToken = this->_lexer.lexerGetNextToken();
}
