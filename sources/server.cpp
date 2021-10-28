#include "../classes/server.hpp"
#include "../classes/request.hpp"

/* Public methods */

void Server::run(int argc, char *argv[])
{
	setServerSettings(argc, argv);
	skeletonDaemon();
	createServer();
	bindServer();
	listenServer();
	while (true)
	{
		fd_set	set;
		int		maxfd;

		FD_ZERO(&set);
		FD_SET(_masterSocket, &set);
		for (const auto& obj: _slaveSockets)
			FD_SET(obj, &set);
		maxfd = std::max(_masterSocket,
			*std::max_element(_slaveSockets.begin(),
			_slaveSockets.end()));
		select(maxfd + 1, &set, nullptr, nullptr, nullptr);
		for (auto iter = _slaveSockets.begin(); iter != _slaveSockets.end(); iter++)
		{
			if (FD_ISSET(*iter, &set))
			{
				int		recvSize;
				char	buffer[512] = {0};

				recvSize = recv(*iter, buffer, 512, MSG_NOSIGNAL);
				if (recvSize == 0 && errno == EAGAIN)
				{
					shutdown(*iter, SHUT_RDWR);
					close(*iter);
					iter = _slaveSockets.erase(iter);
				}
				else if (recvSize > 0)
				{
					handleRequest(*iter, buffer);
				}
			} 
		}
		if (FD_ISSET(_masterSocket, &set))
		{
			acceptNewClient();
		}
	}
}

void Server::terminate(int exitcode)
{
	shutdown(_masterSocket, O_RDWR);
	close(_masterSocket);
	exit(exitcode);
}

/* Private methods */

int Server::setNonBlock(int fd)
{
	int flags;
	
	#if defined(O_NONBLOCK)
    	if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        	flags = 0;
    	return fcntl(fd, F_SETFL, (unsigned) flags | O_NONBLOCK);
	#else
    	flags = 1;
    	return ioctl(fd, FIONBIO, &flags);
	#endif
}

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

void Server::skeletonDaemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
		exit(EXIT_SUCCESS);
	std::cout << "Server PID = " << getpid() << std::endl;

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
  	chdir(_dir.c_str());

    /* Close all open file descriptors */
    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
        close(x);
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
		throw std::runtime_error("Settings setup failed. Incorrect program arguments");
}

void Server::createServer()
{
	_masterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_masterSocket < 0)
		throw std::runtime_error("socket() failed");
}

void Server::bindServer()
{
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	inet_pton(_masterSocket, _ip.c_str(), &_addr.sin_addr.s_addr);
	if (bind(_masterSocket, (const sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("bind() failed");
}

void Server::listenServer()
{
	if (listen(_masterSocket, SOMAXCONN) < 0)
		throw std::runtime_error("listen() failed");
}

void Server::acceptNewClient()
{
	int	newSlaveSocket;

	if ((newSlaveSocket = accept(_masterSocket, nullptr, nullptr)) < 0)
		throw std::runtime_error("accept() failed");
	setNonBlock(newSlaveSocket);
	_slaveSockets.insert(newSlaveSocket);
}

void Server::handleRequest(int slavefd, const char *buffer)
{
	HTTPRequestFabric	*httpRequestFabric = new HTTPRequestCreator();
	HTTPRequest			*request = httpRequestFabric->factoryMethod();
	std::string			responce;

	request->initRequest(buffer);
	responce = request->getResponce(_dir);
	if (send(slavefd, responce.c_str(), responce.length(), MSG_NOSIGNAL) < 0)
		throw std::runtime_error("send() failed");
	delete request;
	delete httpRequestFabric;
}
