
#ifndef SERVERDATA_HPP
# define SERVERDATA_HPP

# include <string>
# include <vector>
# include <map>
# include <utility>

typedef	std::vector<std::string>				VectorOfStrings;
typedef std::map<unsigned short, std::string>	MapOfStatusCode;

class ServerData;

class LocationData
{
public:
	// LOCATION's DATA
	std::string		pathname;
	VectorOfStrings	acceptedMeths;
	bool			autoindex;
	long			limitSize;
	std::string		root;
	VectorOfStrings	index;
	MapOfStatusCode	statusCode;

	// Helper data member
	bool	flag;

public:
	// Constructors && Destructor
	LocationData(const ServerData& ser);
	~LocationData(void);
};

class ServerData
{
public:
	// SERVER's DATA
	std::string		host;
	unsigned short	port;
	VectorOfStrings	serverName;
	VectorOfStrings	acceptedMeths;
	bool			autoindex;
	long			limitSize;
	std::string		root;
	VectorOfStrings	index;
	MapOfStatusCode	statusCode;
	// LOCATION's DATA
	std::vector<LocationData>	location;

public:
	// Constructors && Destructor
	ServerData(void);
	~ServerData(void);
};

#endif
