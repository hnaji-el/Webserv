
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.hpp"
#include "Exceptions.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
			throw ArgumentError();
		Parser	parser(argv[1]);
		parser.parserParse();
	}
	catch (ArgumentError& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	catch (SyntaxError& e)
	{
		std::cerr << "webserv: [ERROR] syntax error near unexpected token `"; 
		std::cerr << e.what() << "'" << std::endl;
		return (1);
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR: opening/reading/closing file" << std::endl;
		return (1);
	}

	return (0);
}
