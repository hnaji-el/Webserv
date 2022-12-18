
#include <iostream>
#include <string>

enum Token {
	ID,
	NAME
};

int	main(void)
{
	char	c = 'a';
	std::string		str = c;

	std::cout << str << std::endl;
	return (0);
}
