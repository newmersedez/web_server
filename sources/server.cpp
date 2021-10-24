#include "../classes/server.hpp"

void Server::setIp(const std::string& ip)
{
	this->_ip = ip;
}

void Server::setPort(const std::string& port)
{
	this->_port = port;
}

void Server::setDirectory(const std::string& directory)
{
	this->_directory = directory;
}

const std::string& Server::getIp() const
{
	return _ip;
}

const std::string& Server::getPort() const
{
	return _port;
}

const std::string& Server::getDiretory() const
{
	return _directory;
}
