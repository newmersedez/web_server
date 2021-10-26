#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

class Server
{
private:
	int					_sockfd;
	struct sockaddr_in	_addr;
	std::string			_ip;
	uint16_t			_port;
	std::string			_dir;
	size_t				_connections;

private:
	bool settingsApplied();
	void executeRequest(const char *buffer);

public:
	Server()
		:	_sockfd(0), _addr({0, 0, 0, 0}), _ip(""),
			_port(0), _dir(""), _connections(0)
	{}

	void setdefaults(int argc, char *argv[]);
	void create();
	void run();
	void terminate();

	~Server();
};
