
#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <string>
# include <cctype>
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
	Token	lexerGetNextToken(void);        // OK
	void	lexerSkipWhitespaces(void);     // OK
	void	lexerAdvance(void);             // OK
	Token	getLparenToken(void);           // OK
	Token	getRparenToken(void);           // OK
	Token	getWordToken(void);             // OK
};

#endif
