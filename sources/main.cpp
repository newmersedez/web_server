#include "../classes/server.hpp"

int set_nonblock(int fd)
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

int main(int argc, char *argv[])
{
	Server	server;

	(void)argc;
	(void)argv;
	try
	{
		server.setdefaults(argc, argv);
		server.create();
		server.run();
	}
	catch(std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		server.terminate();
	}
	server.terminate();
	return 0;
}
