#pragma once

#include <algorithm>
#include <iostream>
#include <thread>
#include <string>
#include <set>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

class Server
{
private:
	int					_masterSocket;
	std::set<int>		_slaveSockets;
	struct sockaddr_in	_addr;
	std::string			_ip;
	uint16_t			_port;
	std::string			_dir;

private:
	int setNonBlock(int fd);
	void setIp(char *ip);
	void setPort(uint16_t port);
	void setDir(char *dir);
	void skeletonDaemon();
	void setServerSettings(int argc, char *argv[]);
	void createServer();
	void bindServer();
	void listenServer();
	void acceptNewClient();
	void handleRequest(int slavefd, const char *buffer);

public:
	Server()
		: _masterSocket(0), _addr({0, 0, {0}, {0}}), _ip(""), _port(0), _dir("")
	{}

	void run(int argc, char *argv[]);
	void terminate(int exitcode);

	~Server()
	{
		shutdown(_masterSocket, SHUT_RDWR);
		close(_masterSocket);
	}
};
