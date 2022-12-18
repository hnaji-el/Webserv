
#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>

enum TokenType
{
	TOKEN_WORD,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
};

class Token
{
private:
	TokenType	_type;
	std::string	_value;

public:
	// Constructors && Destructor
	Token(const TokenType& type, const std::string& value);
	Token(const Token& src);
	~Token(void);

	// Copy assignment operator
	Token&	operator=(const Token& rhs);
};

#endif
