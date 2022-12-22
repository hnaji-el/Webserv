
#ifndef SERVERDATA_HPP
# define SERVERDATA_HPP

# include <string>
# include <vector>
# include <utility>

typedef	std::vector<std::string>					VectorOfStrings;
typedef std::vector<std::pair<int, std::string> >	VectorOfPairs;

class LocationData
{
public:
	// LOCATION's DATA
	bool			GET;
	bool			POST;
	bool			DELETE;
	bool			autoindex;
	size_t			limitSize;
	std::string		root;
	VectorOfStrings	index;
	VectorOfPairs	statusCode;

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
	size_t			limitSize;
	std::string		root;
	VectorOfStrings	index;
	VectorOfPairs	statusCode;
	// LOCATION's DATA
	std::vector<LocationData>	location;

public:
	// Constructors && Destructor
	ServerData(void);
	~ServerData(void);
};

#endif
