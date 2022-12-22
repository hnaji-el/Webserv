
#include "ServerData.hpp"

/*
 * Constructors && Destructors
 */

ServerData::ServerData(void)
	: host("0.0.0.0"), port(80), serverName(1, ""),
	GET(false), POST(false), DELETE(false), autoindex(false), limitSize(1), root("")
{
}

ServerData::~ServerData(void)
{
}

LocationData::LocationData(void)
	: GET(false), POST(false), DELETE(false), autoindex(false), limitSize(1), root("")
{
}

LocationData::~LocationData(void)
{
}
