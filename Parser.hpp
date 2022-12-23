
#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <string>
# include <map>
# include <limits>
# include "Lexer.hpp"
# include "Token.hpp"
# include "ServerData.hpp"
# include "Exceptions.hpp"

class Parser
{
private:
	Lexer	_lexer;
	Token	_curToken;
	Token	_prevToken;
	// AST
	std::vector<ServerData>&	_configData;
	size_t	_szS;
	size_t	_szL;
	// DISPATCH Tables
	typedef std::map<std::string, void (Parser::*)()> Map;
	Map		_serverTable;
	Map		_locationTable;

public:
	// Constructors && Destructor
	Parser(const std::string& fileName, std::vector<ServerData>& configData);
	~Parser(void);

	// ENTRY POINT member function
	void	parserParse(void);

	// parse blocks: server && location
	void	parserParseServer(void);
	void	parserParseLocation(void);

	// parse directives of Server block
	void	parserParseListen(void);
	void	parserParseServerName(void);
	void	parserParseErrorPage(void);
	void	parserParseLimitSize(void);
	void	parserParseAcceptedMethods(void);
	void	parserParseRoot(void);
	void	parserParseIndex(void);
	void	parserParseAutoindex(void);

	// parse directives of Location block
	void	parserParseErrorPageLoc(void);
	void	parserParseLimitSizeLoc(void);
	void	parserParseAcceptedMethodsLoc(void);
	void	parserParseRootLoc(void);
	void	parserParseIndexLoc(void);
	void	parserParseAutoindexLoc(void);

	// HELPER member function
	void	expectedToken(TokenType type);
	bool	isNumber(const std::string& str);
	size_t	stringToNumber(const std::string& str);
	long	checkAndGetNumber(const std::string& str);
	void	checkAndSetMethods(void);
	void	checkAndSetMethodsLoc(void);

	// fill DISPATCH Tables
	void	fillServerTable(void);
	void	fillLocationTable(void);
};

#endif























