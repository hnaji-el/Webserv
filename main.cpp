
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.hpp"
#include "ServerData.hpp"
#include "Exceptions.hpp"

void	visitorVisit(const std::vector<ServerData>& cData);

int	parseConfigFile(int argc, char** argv, std::vector<ServerData>& cData)
{
	try
	{
		if (argc != 2)
			throw Failure("webserv: [ERROR]: Usage: ./webserv [configuration file]");
		Parser	parser(argv[1], cData);
		parser.parserParse();
	}
	catch (Failure& e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	catch (SyntaxError& e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}

	return (0);
}

int	main(int argc, char** argv)
{
	std::vector<ServerData>	cData;

	if (parseConfigFile(argc, argv, cData) == -1)
		return (EXIT_FAILURE);

	visitorVisit(cData);

	return (EXIT_SUCCESS);
}
