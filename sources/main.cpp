#include <experimental/filesystem>
#include <fstream>
#include "../classes/server.hpp"

#define ERROR_FILENAME	"ErrorLog.txt"

namespace fs = std::experimental::filesystem;

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

	try
	{
		fs::remove(ERROR_FILENAME);
		server.run(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::ofstream	stream;

		stream.open(ERROR_FILENAME);
		stream << e.what() << std::endl;
		stream.close();
		std::cerr << "Error detected. Open " << ERROR_FILENAME << std::endl;
	}
	server.terminate(EXIT_SUCCESS);
	return 0;
}
