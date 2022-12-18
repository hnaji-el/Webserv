
#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <string>
# include "Token.hpp"

class Lexer
{
private:
	std::string	_line;
	size_t		_curIndex;
	char		_curChar;

public:
	Lexer(const std::string& line);
	~Lexer(void);

	// member functions: ...
	Token	lexerGetNextToken(void);
	void	lexerSkipWhitespaces(void);
	void	lexerAdvance(void);
	Token	advanceAndReturn(Token* token);
};

#endif
