#include "../classes/server.hpp"
#include "../classes/client.hpp"

#include <iostream>
#include <unistd.h>
#include <ctype.h>

void setServerDefaults(int argc, char *argv[], Server& HTTPServer)
{
	const char	*optString = "h:p:d:";
	int			opt = 0;

	while ((opt = getopt(argc, argv, optString)) != -1)
	{
		switch (opt)
		{
		case 'h':
			HTTPServer.setIp(std::string(optarg));
			break;
		case 'p':
			HTTPServer.setPort(atoi(optarg));
			break;
		case 'd':
			HTTPServer.setDirectory(std::string(optarg));
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	Server	server;

	setServerDefaults(argc, argv, server);
	try
	{
		server.create();
		server.run();
	}
	catch(std::runtime_error& ex)
	{
		std::cerr << ex.what() << std::endl;
		server.terminate();
	}
	return 0;
}
