#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

class Client
{
private:
	int					_sockfd;
	struct sockaddr_in	_addr;
	std::string			_ip;
	std::string			_port;

public:
	Client() = default;

	Client(const std::string& ip, const std::string& port)
		: _ip(ip), _port(port)
	{}

	void setIp(const std::string& ip);
	void setPort(const std::string& port);

	const std::string& getIp() const;
	const std::string& getPort() const;

	int	socket(/* int domain, int type, int protocol */);
	int	connect(/* int sockfd, const struct sockaddr *addr, socklen_t addrlen */);
	int	recv(/* int sockfd, void *buf, size_t len, int flags */);
	int	send(/* int sockfd, const void *buf, size_t len, int flags */);
	int	shutdown(/* int sockfd, int flags */);
	int	close(/* int sockfd */);

	~Client() = default;
};
