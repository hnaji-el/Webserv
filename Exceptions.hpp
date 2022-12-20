
#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <exception>
# include <string>

class ArgumentError : std::exception
{
public:
	ArgumentError(void) { }
	virtual ~ArgumentError(void) throw() { }

	virtual const char*	what() const throw()
	{
		return ("ERROR: Usage: ./webserv [configuration file]");
	}
};

class SyntaxError : std::exception
{
private:
	const std::string	_msg;

public:
	SyntaxError(const std::string& msg) : _msg(msg) { }
	virtual ~SyntaxError(void) throw() { }

	virtual const char*	what() const throw()
	{
		return (this->_msg.c_str());
	}
};

#endif
