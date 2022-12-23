
#include "Parser.hpp"

/*
 * Constructors && Destructor
 */

Parser::Parser(const std::string& fileName, std::vector<ServerData>& configData)
	: _lexer(fileName), _configData(configData), _szS(0), _szL(0)
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
	this->_serverTable["autoindex"] = &Parser::parserParseAutoindex;
	this->_serverTable["location"] = &Parser::parserParseLocation;
}

void	Parser::fillLocationTable(void)
{
	this->_locationTable["error_page"] = &Parser::parserParseErrorPageLoc;
	this->_locationTable["limit_client_body_size"] = &Parser::parserParseLimitSizeLoc;
	this->_locationTable["accepted_methods"] = &Parser::parserParseAcceptedMethodsLoc;
	this->_locationTable["root"] = &Parser::parserParseRootLoc;
	this->_locationTable["index"] = &Parser::parserParseIndexLoc;
	this->_locationTable["autoindex"] = &Parser::parserParseAutoindexLoc;
}

/*
 * ENTRY POINT member function
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
}

void	Parser::parserParseServer(void)
{
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	this->_configData.push_back(ServerData());
	this->_szS++;
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
}

void	Parser::parserParseLocation(void)
{
	this->expectedToken(TOKEN_WORD);
	this->expectedToken(TOKEN_LPAREN);
	this->expectedToken(TOKEN_EOL);

	this->_configData[this->_szS - 1].location.push_back(LocationData());
	this->_szL++;
	while (this->_curToken.type != TOKEN_RPAREN)
	{
		while (this->_curToken.type == TOKEN_EOL)
			this->expectedToken(TOKEN_EOL);
		if (this->_curToken.type == TOKEN_RPAREN)
			break ;

		Map::iterator	iter = this->_locationTable.find(this->_curToken.value);
		if (iter == this->_locationTable.end())
			throw SyntaxError(this->_curToken.value);
		this->expectedToken(TOKEN_WORD);
		(this->*(iter->second))();
	}
	this->expectedToken(TOKEN_RPAREN);
	this->expectedToken(TOKEN_EOL);
}

/*
 * Parse directives of Server block
 */

void	Parser::parserParseListen(void)
{
	long	port = 0;

	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].host = this->_prevToken.value;

	this->expectedToken(TOKEN_WORD);
	port = this->checkAndGetNumber(this->_prevToken.value);
	if (port < 1 || port > 65535)
		throw SyntaxError(this->_prevToken.value);
	this->_configData[this->_szS - 1].port = port;

	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseServerName(void)
{
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].serverName.push_back(this->_prevToken.value);

	while (this->_curToken.type == TOKEN_WORD)
	{
		this->expectedToken(TOKEN_WORD);
		this->_configData[this->_szS - 1].serverName.push_back(this->_prevToken.value);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseErrorPage(void)
{
	long	num = 0;

	this->expectedToken(TOKEN_WORD);
	num = this->checkAndGetNumber(this->_prevToken.value);
	if (num < 100 || num > 599)
		throw SyntaxError(this->_prevToken.value);
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].statusCode[num] = this->_prevToken.value;

	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseLimitSize(void)
{
	long	num = 0;

	this->expectedToken(TOKEN_WORD);
	num = this->checkAndGetNumber(this->_prevToken.value);
	if (num == -1)
		throw SyntaxError(this->_prevToken.value);
	this->_configData[this->_szS - 1].limitSize = num;
	
	this->expectedToken(TOKEN_EOL);
}

void	Parser::checkAndSetMethods(void)
{
	if (this->_prevToken.value == "GET")
		this->_configData[this->_szS - 1].GET = true;
	else if (this->_prevToken.value == "POST")
		this->_configData[this->_szS - 1].POST = true;
	else if (this->_prevToken.value == "DELETE")
		this->_configData[this->_szS - 1].DELETE = true;
	else
		throw SyntaxError(this->_prevToken.value);
}

void	Parser::parserParseAcceptedMethods(void)
{
	this->expectedToken(TOKEN_WORD);
	this->checkAndSetMethods();
	for (size_t i = 0; i < 2 && this->_curToken.type == TOKEN_WORD; i++) {
		this->expectedToken(TOKEN_WORD);
		this->checkAndSetMethods();
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseRoot(void)
{
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].root = this->_prevToken.value;
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseIndex(void)
{
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].index.push_back(this->_prevToken.value);

	while (this->_curToken.type == TOKEN_WORD)
	{
		this->expectedToken(TOKEN_WORD);
		this->_configData[this->_szS - 1].index.push_back(this->_prevToken.value);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAutoindex(void)
{
	this->expectedToken(TOKEN_WORD);
	if (this->_prevToken.value != "on")
		throw SyntaxError(this->_prevToken.value);
	this->_configData[this->_szS - 1].autoindex = true;
	this->expectedToken(TOKEN_EOL);
}

/*
 * Parse directives of Location block
 */

void	Parser::parserParseErrorPageLoc(void)
{
	long	num = 0;

	this->expectedToken(TOKEN_WORD);
	num = this->checkAndGetNumber(this->_prevToken.value);
	if (num < 100 || num > 599)
		throw SyntaxError(this->_prevToken.value);
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].location[this->_szL - 1].statusCode[num] = this->_prevToken.value;

	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseLimitSizeLoc(void)
{
	long	num = 0;

	this->expectedToken(TOKEN_WORD);
	num = this->checkAndGetNumber(this->_prevToken.value);
	if (num == -1)
		throw SyntaxError(this->_prevToken.value);
	this->_configData[this->_szS - 1].location[this->_szL - 1].limitSize = num;
	
	this->expectedToken(TOKEN_EOL);
}

void	Parser::checkAndSetMethodsLoc(void)
{
	if (this->_prevToken.value == "GET")
		this->_configData[this->_szS - 1].location[this->_szL - 1].GET = true;
	else if (this->_prevToken.value == "POST")
		this->_configData[this->_szS - 1].location[this->_szL - 1].POST = true;
	else if (this->_prevToken.value == "DELETE")
		this->_configData[this->_szS - 1].location[this->_szL - 1].DELETE = true;
	else
		throw SyntaxError(this->_prevToken.value);
}

void	Parser::parserParseAcceptedMethodsLoc(void)
{
	this->expectedToken(TOKEN_WORD);
	this->checkAndSetMethodsLoc();
	for (size_t i = 0; i < 2 && this->_curToken.type == TOKEN_WORD; i++) {
		this->expectedToken(TOKEN_WORD);
		this->checkAndSetMethodsLoc();
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseRootLoc(void)
{
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].location[this->_szL - 1].root = this->_prevToken.value;
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseIndexLoc(void)
{
	this->expectedToken(TOKEN_WORD);
	this->_configData[this->_szS - 1].location[this->_szL - 1].index.push_back(this->_prevToken.value);

	while (this->_curToken.type == TOKEN_WORD)
	{
		this->expectedToken(TOKEN_WORD);
		this->_configData[this->_szS - 1].location[this->_szL - 1].index.push_back(this->_prevToken.value);
	}
	this->expectedToken(TOKEN_EOL);
}

void	Parser::parserParseAutoindexLoc(void)
{
	this->expectedToken(TOKEN_WORD);
	if (this->_prevToken.value != "on")
		throw SyntaxError(this->_prevToken.value);
	this->_configData[this->_szS - 1].location[this->_szL - 1].autoindex = true;
	this->expectedToken(TOKEN_EOL);
}

/*
 * Helper member functions
 */

void	Parser::expectedToken(TokenType type)
{
	if (this->_curToken.type != type)
		throw SyntaxError(this->_curToken.value);

	this->_prevToken = this->_curToken;
	this->_curToken = this->_lexer.lexerGetNextToken();
}

bool	Parser::isNumber(const std::string& str)
{
	return (str.find_first_not_of("0123456789") == std::string::npos);
}

size_t	Parser::stringToNumber(const std::string& str)
{
	size_t	num = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		num *= 10;
		num = num + (str[i] - '0');
	}
	return (num);
}

long	Parser::checkAndGetNumber(const std::string& str)
{
	size_t	num = 0;

	if (!this->isNumber(str) || str.size() > 19 ||
		(num = this->stringToNumber(str)) > (size_t)std::numeric_limits<long>::max())
	{
		return (-1);
	}
	return (num);
}
