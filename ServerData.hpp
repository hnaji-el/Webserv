
#ifndef SERVERDATA_HPP
# define SERVERDATA_HPP

# include <string>
# include <vector>
# include <map>
# include <utility>

typedef	std::vector<std::string>				VectorOfStrings;
typedef std::map<unsigned short, std::string>	MapOfStatusCode;

class LocationData
{
public:
	// LOCATION's DATA
	std::string		pathname;
	bool			GET;
	bool			POST;
	bool			DELETE;
	bool			autoindex;
	long			limitSize;
	std::string		root;
	VectorOfStrings	index;
	MapOfStatusCode	statusCode;

public:
	// Constructors && Destructor
	LocationData(void);
	~LocationData(void);
};

class ServerData
{
public:
	// SERVER's DATA
	std::string		host;
	unsigned short	port;
	VectorOfStrings	serverName;
	bool			GET;
	bool			POST;
	bool			DELETE;
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
