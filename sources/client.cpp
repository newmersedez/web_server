#include "../classes/client.hpp"

/* Class methods */

void Client::setIp(const std::string& ip)
{
	this->_ip = ip;
}

void Client::setPort(const std::string& port)
{
	this->_port = port;
}

const std::string& Client::getIp() const
{
	return _ip;
}

const std::string& Client::getPort() const
{
	return _port;
}

/* Additional functions */
