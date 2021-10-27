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

void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
	{
		std::cout << "fork1 parent = " << getpid() << std::endl;
        exit(EXIT_SUCCESS);
	}
	std::cout << "fork1 child = " << getpid() << std::endl;

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
	{
		std::cout << "fork2 parent = " << getpid() << std::endl;
        exit(EXIT_SUCCESS);
	}
	std::cout << "fork2 child = " << getpid() << std::endl;

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }
}

int main(int argc, char *argv[])
{
	Server	server;

	skeleton_daemon();
	try
	{
		server.run(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	server.terminate(EXIT_SUCCESS);
	return 0;
}
