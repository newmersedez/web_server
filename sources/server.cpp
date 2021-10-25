#include "../classes/server.hpp"

/* Class methods */

inline void Server::setIp(const std::string& ip)
{
	this->_ip = ip;
}

inline void Server::setPort(const uint16_t& port)
{
	this->_port = port;
}

inline void Server::setDirectory(const std::string& directory)
{
	this->_directory = directory;
}

const std::string& Server::getIp() const
{
	return _ip;
}

const uint16_t& Server::getPort() const
{
	return _port;
}

const std::string& Server::getDiretory() const
{
	return _directory;
}

void Server::create()
{
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throw std::runtime_error("socket() failed");
	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("bind() failed");
	if (listen(_sockfd, SOMAXCONN) < 0)
		throw std::runtime_error("listen() failed");
}

void Server::run()
{
	while (true)
	{
		int		slavefd;
		char	buffer[1024];

		if ((slavefd = accept(_sockfd, 0, 0)) < 0)	
			throw std::runtime_error("accept() failed");
		recv(slavefd, buffer, 1023, MSG_NOSIGNAL);
		printf("buffer = %s", buffer);
		shutdown(slavefd, SHUT_RDWR);
		close(slavefd);
	}
}

void Server::terminate()
{
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
}

/* Additional functions */
