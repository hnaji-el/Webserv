
#include "./parseConfigFile/parseConfigFile.hpp"

int	main(int argc, char** argv)
{
	std::vector<ServerData>	cData;

	if (parseConfigFile(argc, argv, cData) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
