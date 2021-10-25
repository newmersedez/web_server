#pragma once

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

class Server
{
private:
	int					_sockfd;
	struct sockaddr_in	_addr;
	std::string			_ip;
	uint16_t			_port;
	std::string			_directory;

public:
	Server() = default;

	explicit Server(const std::string& ip, const uint16_t & port, const std::string& dir)
		: _ip(ip), _port(port), _directory(dir)
	{}
	
	void setIp(const std::string& ip);
	void setPort(const uint16_t& port);
	void setDirectory(const std::string& directory);
	void create();
	void run();
	void terminate();

	const std::string& getIp() const;
	const uint16_t& getPort() const;
	const std::string& getDiretory() const;

	~Server()
	{
		shutdown(_sockfd, SHUT_RDWR);
		close(_sockfd);
	}
};
