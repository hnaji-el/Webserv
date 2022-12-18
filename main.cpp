
#include <iostream>
#include <fstream>
#include <string>

int	main(int argc, char** argv)
{
	std::ifstream	fileStream;
	std::string		str;

	if (argc != 2)
	{
		std::cout << "ERROR: Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		fileStream.open(argv[1]);
		while (!fileStream.eof())
		{
			std::getline(fileStream, str);
			size_t i = 0;
			for (;str[i] != '\0'; i++) {
				std::cout << str[i] << "|";
			}
			if (str[i] == '\0') std::cout << "....";
			std::cout << std::endl;
		}
		fileStream.close();
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: opening/reading/closing file" << std::endl;
		return (1);
	}

	return (0);
}
