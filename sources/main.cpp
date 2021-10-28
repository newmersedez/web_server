#include "../classes/server.hpp"
#include <experimental/filesystem>
#include <fstream>

#define ERROR_FILENAME	"ErrorLog.txt"
namespace fs = std::experimental::filesystem;

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
		std::cerr << "Error detected. Open <server dir>/" << ERROR_FILENAME << std::endl;
	}
	server.terminate(EXIT_SUCCESS);
	return 0;
}
