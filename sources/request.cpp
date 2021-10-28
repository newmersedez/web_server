#include "../classes/request.hpp"

// GET /other.html HTTP/1.0
// Host: 127.0.0.1:1234
// User-Agent: curl/7.68.0
// Accept: */* 

/*

ss << "HTTP/1.0 404 NOT FOUND";
		ss << "\r\n";
		ss << "Content-length: ";
		ss << 0;
		ss << "\r\n";
		ss << "Content-Type: text/html";
		ss << "\r\n\r\n";

*/

void HTTPRequest::initRequest(const char *buffer)
{
	std::string	strBuffer = std::string(buffer);
	size_t		pos;

	pos = strBuffer.find("GET /");
	if (pos != std::string::npos)
	{
		this->_method = "GET";
		strBuffer.erase(0, pos + 5);
	}
	pos = strBuffer.find(" HTTP/");
	if (pos != std::string::npos)
	{
		this->_purpose = strBuffer.substr(0, pos);
		strBuffer.erase(0, pos + 6);
		this->_version = strBuffer.substr(0, 3);
		strBuffer.erase(0, 5);
	}
}

std::string HTTPRequest::getResponce(const std::string& path) const
{
	(void)path;
	std::stringstream ss;

	ss << "HTTP/" << this->_version;
	ss << " 404 NOT FOUND";
	ss << "\r\n";
	ss << "Content-length: ";
	ss << 0;
	ss << "\r\n";
	ss << "Content-Type: text/html";
	ss << "\r\n\r\n";
	
	return ss.str();
}

HTTPRequest *HTTPRequestCreator::factoryMethod() const
{
	return new HTTPRequest();
}
