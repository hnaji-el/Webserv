
#include <iostream>
#include <string>

enum Test {
	ID = 7,
	WORD = 9
};

int	main(void)
{
	Test	ts = WORD;

	std::cout << ts << std::endl;
	return (0);
}
