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

	server.run(argc, argv);
	server.terminate(EXIT_SUCCESS);
	return 0;
}
