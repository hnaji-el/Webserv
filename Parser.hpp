
#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"
# include "Token.hpp"

class Parser
{
private:
	Token	curToken;
	Token	prevToken;
	// NOTE: ...

public:
	Parser(void);
	~Parser(void);

	// member functions [ Parser ]: ...
};

#endif
