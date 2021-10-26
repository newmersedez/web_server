#include "../classes/server.hpp"

Server::~Server()
{
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
}

/* Private methods */

bool Server::settingsApplied() const
{
	if (_ip == "" || _port == 0 || _dir == "")
		return false;
	return true;
}

std::string Server::executeRequest(const std::string& request) const
{
	(void)request;
	return (std::string("lalka"));
}

/* Public methods */

void Server::setdefaults(int argc, char *argv[])
{
	const char	*optString = "h:p:d:";
	size_t		flags = 0;
	int			opt = 0;

	while ((opt = getopt(argc, argv, optString)) != -1)
	{
		switch (opt)
		{
		case 'h':
			this->_ip = std::string(optarg);
			++flags;
			break;
		case 'p':
			this->_port = atoi(optarg);
			++flags;
			break;
		case 'd':
			this->_dir = std::string(optarg);
			++flags;
			break;
		}
	}
	if (flags != 3)
		throw std::invalid_argument("Invalid arguments");
}

void Server::create()
{
	if (settingsApplied() == false)
		throw std::runtime_error("Server settings were not applied");
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	inet_pton(_sockfd, _ip.c_str(), &_addr.sin_addr.s_addr);
	// _addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throw std::runtime_error("socket() failed");
	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("bind() failed");
	if (listen(_sockfd, SOMAXCONN) < 0)
		throw std::runtime_error("listen() failed");
}

void Server::run()
{
	if (settingsApplied() == false)
		throw std::runtime_error("Server settings were not applied");
	while (true)
	{
		int			slavefd;
		std::string	request;
		std::string	response;
		static char	buffer[128] = {0};

		if ((slavefd = accept(_sockfd, nullptr, nullptr)) < 0)	
			throw std::runtime_error("accept() failed");
		if (recv(slavefd, buffer, 128, MSG_NOSIGNAL) < 0)
			throw std::runtime_error("recv() failed");
		request = buffer;
		response = executeRequest(request);
		if (send(slavefd, response.c_str(), response.length(), MSG_NOSIGNAL) < 0)
			throw std::runtime_error("send() failed");
		request.clear();
		response.clear();
		shutdown(slavefd, SHUT_RDWR);
		close(slavefd);
	}
}

void Server::terminate()
{
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	exit(EXIT_SUCCESS);
}
