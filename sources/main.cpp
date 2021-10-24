#include "../headers/server.hpp"

class Server
{
private:
	std::string	_ip;
	std::string _port;
	std::string _directory;

public:
	Server() = default;

	explicit Server(std::string ip, std::string port, std::string dir)
		: _ip(ip), _port(port), _directory(dir)
	{}
	
	void setIp(const std::string& ip) { this->_ip = ip; }
	void setPort(const std::string& port) { this->_port = port; }	
	void setDirectory(const std::string& directory) { this->_directory = directory; }

	const std::string& getIp() const { return _ip; }
	const std::string& getPort() const { return _port; }
	const std::string& getDiretory() const { return _directory; }
	
	~Server() = default;
};

void getServerDefaults(int argc, char *argv[], Server& server)
{
	const char	*optString = "h:p:d:";
	int			opt = 0;

	while ((opt = getopt(argc, argv, optString)) != -1)
	{
		switch (opt)
		{
		case 'h':
			server.setIp(std::string(optarg));
			break;
		case 'p':
			server.setPort(std::string(optarg));
			break;
		case 'd':
			server.setDirectory(std::string(optarg));
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	Server	server;

	getServerDefaults(argc, argv, server);
	std::cout << server.getIp() << " " << server.getPort() << " " << server.getDiretory() << "\n";
	return 0;
}
