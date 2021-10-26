#pragma once

#include <iostream>
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

private:
	bool settingsApplied() const;
	std::string executeRequest(const std::string& request) const;

public:
	Server()
		: _sockfd(0), _addr({0, 0, 0, 0}), _ip(""), _port(0), _dir("")
	{}

	void setdefaults(int argc, char *argv[]);
	void create();
	void run();
	void terminate();

	~Server();
};
