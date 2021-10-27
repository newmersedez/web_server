#include "../classes/http_request.hpp"

/* Public methods */

void HTTPRequest::createRequest(const char *buffer)
{
	(void)buffer;
}

std::string HTTPRequest::getResponce()
{
	return ("recieved");
}

/* Private methods */

std::string message404()
{
	return ("ahaha\n");
}

std::string message200()
{
	return ("ahaha\n");
}
