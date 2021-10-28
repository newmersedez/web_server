#include "../classes/request.hpp"

// GET /other.html HTTP/1.0
// Host: 127.0.0.1:1234
// User-Agent: curl/7.68.0
// Accept: */* 

/*

sstream << "HTTP/1.0 404 NOT FOUND";
		sstream << "\r\n";
		sstream << "Content-length: ";
		sstream << 0;
		sstream << "\r\n";
		sstream << "Content-Type: text/html";
		sstream << "\r\n\r\n";

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

std::string HTTPRequest::getResponce(const std::string& dir) const
{
	std::string	responce;
	fs::path	fullpath(dir);

	fullpath += "/" + _purpose;
	if (fs::exists(fullpath))
		responce = message200(fullpath);
	else
		responce = message404();	
	return responce;
}

std::string HTTPRequest::message200(const fs::path& path) const
{
	std::stringstream	sstream;

	sstream << "HTTP/" << _version << " 200 OK";
	sstream << "\r\n";
	sstream << "Content-length: ";
	sstream << fs::file_size(path);
	sstream << "\r\n";
	sstream << "Content-Type: text/html";
	sstream << "\r\n\r\n";
	return sstream.str();
}

std::string HTTPRequest::message404() const
{
	std::stringstream	sstream;

	sstream << "HTTP/" << _version << " 404 NOT FOUND";
	sstream << "\r\n";
	sstream << "Content-length: ";
	sstream << 0;
	sstream << "\r\n";
	sstream << "Content-Type: text/html";
	sstream << "\r\n\r\n";
	return sstream.str();
}

HTTPRequest *HTTPRequestCreator::factoryMethod() const
{
	return new HTTPRequest();
}
