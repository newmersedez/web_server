#include "../classes/server.hpp"

/* Public methods */

void Server::run(int argc, char *argv[])
{
	setServerSettings(argc, argv);
	createServer();
	bindServer();
	listenServer();
	while (true)
	{
		int		slavefd;
		char	buffer[128] = {0};

		if ((slavefd = accept(_sockfd, nullptr, nullptr)) < 0)
			throw std::runtime_error("accept failed");
		if (recv(slavefd, buffer, 127, MSG_NOSIGNAL) < 0)
			throw std::runtime_error("recv() failed");
		printf("buffer = %s\n", buffer);
		std::string	responce = "ahahahahahahaa lalkaaa";
		if (send(slavefd, responce.c_str(), responce.length() + 1, MSG_NOSIGNAL) < 0)
			throw std::runtime_error("send() failed");
		shutdown(slavefd, O_RDWR);
		close(slavefd);
	}
}

void Server::terminate(int exitcode)
{
	shutdown(_sockfd, O_RDWR);
	close(_sockfd);
	exit(exitcode);
}

/* Private methods */

inline void Server::setIp(char *ip)
{
	this->_ip = std::string(ip);
}

inline void Server::setPort(uint16_t port)
{
	this->_port = port;
}

inline void Server::setDir(char *dir)
{
	this->_dir = std::string(dir);
}

void Server::setServerSettings(int argc, char *argv[])
{
	const char	*optString = "h:p:d:";
	int			opt = 0;

	while ((opt = getopt(argc, argv, optString)) != -1)
	{
		switch (opt)
		{
		case 'h':
			setIp(optarg);
			break;
		case 'p':
			setPort(static_cast<uint16_t>(atoi(optarg)));
			break;
		case 'd':
			setDir(optarg);
			break;
		}
	}
	if (_ip == "" || _port == 0 || _dir == "")
		throw std::runtime_error("Settings setup failed");
}

void Server::createServer()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sockfd < 0)
		throw std::runtime_error("socket() failed");
}

void Server::bindServer()
{
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	inet_pton(_sockfd, _ip.c_str(), &_addr.sin_addr.s_addr);
	if (bind(_sockfd, (const sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("bind() failed");
}

void Server::listenServer()
{
	if (listen(_sockfd, SOMAXCONN) < 0)
		throw std::runtime_error("listen() failed");
}
