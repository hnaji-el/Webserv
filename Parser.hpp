
#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <string>
# include "Lexer.hpp"
# include "Token.hpp"
# include "Exceptions.hpp"

class Parser
{
private:
	Lexer	_lexer;
	Token	_curToken;

public:
	// Constructors && Destructor
	Parser(const std::string& fileName);
	~Parser(void);

	// ENTRY POINT member function
	void	parserParse(void);

	// parse blocks: server && location
	void	parserParseServer(void);
	void	parserParseLocation(void);

	// parse directives
	void	parserParseListen(void);
	void	parserParseServerName(void);
	void	parserParseErrorPage(void);
	void	parserParseLimitSize(void);
	void	parserParseAcceptedMethods(void);
	void	parserParseRoot(void);
	void	parserParseIndex(void);
	void	parserParseAutoIndex(void);

	// HELPER member function
	void	expectedToken(TokenType type);
};

#endif













