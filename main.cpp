
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.hpp"
#include "ServerData.hpp"
#include "Exceptions.hpp"

int		parseConfigFile(int argc, char** argv, std::vector<ServerData>& cData)
{
	try
	{
		if (argc != 2)
			throw ArgumentError();
		Parser	parser(argv[1], cData);
		parser.parserParse();
	}
	catch (ArgumentError& e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	catch (SyntaxError& e)
	{
		std::cerr << "webserv: [ERROR] syntax error near unexpected token `"; 
		std::cerr << e.what() << "'" << std::endl;
		return (-1);
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR: opening/reading/closing file" << std::endl;
		return (-1);
	}

	return (0);
}

int		main(int argc, char** argv)
{
	std::vector<ServerData>	configData;

	if (parseConfigFile(argc, argv, configData) == -1)
		return (-1);

	std::cout << configData.size() << std::endl;
	return (0);
}
