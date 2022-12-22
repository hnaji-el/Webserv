
#ifndef AST_HPP
# define AST_HPP

# include <string>
# include <vector>
# include <utility>

struct	LocationDATA
{
public:
	// LOCATION's DATA
	std::vector<std::string>	server_name;
	std::vector<std::pair<int, std::string> >	status_code;
	long	limit_size;
	bool	GET;
	bool	POST;
	bool	DELETE;
	std::string		root;
	std::string		autoindex
	std::vector<std::string>	index;

public:
	// Constructors && Destructor
	LocationData(void);
	~LocationData(void);
};

struct ServerData
{
public:
	// SERVER's DATA
	std::string	host;
	int			port;
	std::vector<std::string>	server_name;
	std::vector<std::pair<int, std::string> >	status_code;
	long	limit_size;
	bool	GET;
	bool	POST;
	bool	DELETE;
	std::string		root;
	std::string		autoindex
	std::vector<std::string>	index;
	// LOCATION's DATA
	std::vector<Location>	location;

public:
	// Constructors && Destructor
	ServerData(void);
	~ServerData(void);
};

#endif
