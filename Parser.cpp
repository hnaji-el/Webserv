
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
	// replace all of these forest if condition by dispatching ...
	if (this->_curToken.value == "listen") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseListen();
	}
	if (this->_curToken.value == "server_name") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseServerName();
	}
	if (this->_curToken.value == "error_page") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseErrorPage();
	}
	if (this->_curToken.value == "limit_client_body_size") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseLimitSize();
	}
	if (this->_curToken.value == "accepted_methods") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseAcceptedMethods();
	}
	if (this->_curToken.value == "root") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseRoot();
	}
	if (this->_curToken.value == "index") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseIndex();
	}
	if (this->_curToken.value == "autoindex") {
		this->_curToken = this->_lexer.lexerGetNextToken();
		this->parserParseAutoIndex();
	}
}

void	Parser::expectedToken(TokenType type)
{
	if (this->_curToken.type != type) {
		throw SyntaxError(this->_curToken.value);
	}
	// TODO: ADD data to AST (TOKEN_WORD) ...
	this->_curToken = this->_lexer.lexerGetNextToken();
}

void	Parser::parserParseServer(void)
{
}

void	Parser::parserParseLocation(void)
{
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
