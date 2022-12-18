
#include "Token.hpp"

Token::Token(const TokenType& type, const std::string& value)
	: _type(type), _value(value)
{
}

Token::Token(const Token& src)
	: _type(src._type), _value(src._value)
{
}

Token::~Token(void)
{
}

// Copy assignment operator
Token&	Token::operator=(const Token& rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs._type;
		this->_value = rhs._value;
	}

	return (*this);
}
