#pragma once

#include <iostream>
#include <string>

#include "httprequest.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

class Server
{
private:
	int					_sockfd;
	struct sockaddr_in	_addr;
	std::string			_ip;
	uint16_t			_port;
	std::string			_dir;

private:
	void setIp(char *ip);
	void setPort(uint16_t port);
	void setDir(char *dir);
	void skeletonDaemon();
	void setServerSettings(int argc, char *argv[]);
	void createServer();
	void bindServer();
	void listenServer();

public:
	Server()
		: _sockfd(0), _addr({0, 0, {0}, {0}}), _ip(""), _port(0), _dir("")
	{}

	void run(int argc, char *argv[]);
	void terminate(int exitcode);

	~Server()
	{
		shutdown(_sockfd, SHUT_RDWR);
		close(_sockfd);
	}
};
