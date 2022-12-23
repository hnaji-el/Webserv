
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "ServerData.hpp"

void	visitorVisit(const std::vector<ServerData>& cData);
void	visitorVisitServer(const ServerData& serData);
void	visitorVisitLocation(const std::vector<LocationData>& loc);
void	visitorVisitLocation_(const LocationData& locData);
void	visitorVisitServerName(const VectorOfStrings& serName);
void	visitorVisitIndex(const VectorOfStrings& index);
void	visitorVisitStatusCode(const MapOfStatusCode& sCode);

void	visitorVisitServerName(const VectorOfStrings& serName)
{
	std::cout << "serverName: ";
	for (size_t i = 0; i < serName.size(); i++) {
		std::cout << serName[i] << " ";
	}
	std::cout << std::endl;
}

void	visitorVisitIndex(const VectorOfStrings& index)
{
	std::cout << "index: ";
	for (size_t i = 0; i < index.size(); i++) {
		std::cout << index[i] << " ";
	}
	std::cout << std::endl;
}

void	visitorVisitStatusCode(const MapOfStatusCode& sCode)
{
	std::cout << "statusCode: ";
	MapOfStatusCode::const_iterator	it;

	for (it = sCode.begin(); it != sCode.end(); ++it) {
		std::cout << "[" << it->first << ", " << it->second << "]" << " ";
	}
	std::cout << std::endl;
}

void	visitorVisitLocation_(const LocationData& locData)
{
	std::cout << "pathname: " << locData.pathname << std::endl;
	std::cout << "GET: " << locData.GET << std::endl;
	std::cout << "POST: " << locData.POST << std::endl;
	std::cout << "DELETE: " << locData.DELETE << std::endl;
	std::cout << "autoindex: " << locData.autoindex << std::endl;
	std::cout << "limitSize: " << locData.limitSize << std::endl;
	std::cout << "root: " << locData.root << std::endl;
	visitorVisitIndex(locData.index);
	visitorVisitStatusCode(locData.statusCode);
}

void	visitorVisitLocation(const std::vector<LocationData>& loc)
{
	for (size_t i = 0; i < loc.size(); i++)
	{
		std::cout << "                  LOCATION: " << i + 1 << std::endl;
		visitorVisitLocation_(loc[i]);
	}
}

void	visitorVisitServer(const ServerData& serData)
{
	std::cout << std::boolalpha;

	std::cout << "host: " << serData.host << std::endl;
	std::cout << "port: " << serData.port << std::endl;
	visitorVisitServerName(serData.serverName);
	std::cout << "GET: " << serData.GET << std::endl;
	std::cout << "POST: " << serData.POST << std::endl;
	std::cout << "DELETE: " << serData.DELETE << std::endl;
	std::cout << "autoindex: " << serData.autoindex << std::endl;
	std::cout << "limitSize: " << serData.limitSize << std::endl;
	std::cout << "root: " << serData.root << std::endl;
	visitorVisitIndex(serData.index);
	visitorVisitStatusCode(serData.statusCode);
	visitorVisitLocation(serData.location);
}

void	visitorVisit(const std::vector<ServerData>& cData)
{
	for (size_t i = 0; i < cData.size(); i++)
	{
		std::cout << "###################################################" << std::endl;
		std::cout << "###################################################" << std::endl;
		std::cout << "                    SERVER: " << i + 1 << std::endl;
		visitorVisitServer(cData[i]);
	}
}
