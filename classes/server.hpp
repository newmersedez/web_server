#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

class Server
{
private:
	int					_sockfd;
	struct sockaddr_in	_addr;
	std::string			_ip;
	std::string			_port;
	std::string			_directory;

public:
	Server() = default;

	explicit Server(const std::string& ip, const std::string& port,
				const std::string& dir)
		: _ip(ip), _port(port), _directory(dir)
	{}
	
	void	setIp(const std::string& ip);
	void	setPort(const std::string& port);
	void	setDirectory(const std::string& directory);

	const std::string&	getIp() const;
	const std::string&	getPort() const;
	const std::string&	getDiretory() const;

	int	socket(/* int domain, int type, int protocol */);
	int	bind(/* int sockfd, struct sockaddr *addr, size_t size */);
	int	listen(/* int sockfd, int backlog(SOMAXCONN) */);
	int	accept(/* int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen */);
	int	recv(/* int sockfd, void *buf, size_t len, int flags */);
	int	send(/* int sockfd, const void *buf, size_t len, int flags */);
	int	shutdown(/* int sockfd, int flags */);
	int	close(/* int sockfd */);

	~Server() = default;
};
