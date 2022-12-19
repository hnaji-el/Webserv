
#include <iostream>
#include <string>

int	main(void)
{
	char	arr[] = "hamid";
	std::string	str;

	for (size_t i = 0; i < 5; i++)
		str += arr[i];

	std::cout << arr << std::endl;
	if (str[4] == '\0')
		std::cout << str << std::endl;

	return (0);
}
