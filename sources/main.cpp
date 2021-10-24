#include "../headers/header.hpp"

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
