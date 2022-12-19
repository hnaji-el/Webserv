
#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <exception>

class ArgumentError : std::exception
{
public:
	virtual const char*	what() const throw()
	{
		return ("ERROR: Usage: ./webserv [configuration file]");
	}
};

#endif
