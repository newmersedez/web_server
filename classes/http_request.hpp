#pragma once

#include <string>
#include <cstdlib>

class HTTPRequest
{
private:
	std::string	_method;
	std::string	_path;
	std::string	_version;
	std::string	_connectStatus;
	std::string	_connectType;
	size_t		_connectLength;

public:
	HTTPRequest()
		: _method(""), _path(""), _version(""),
		_connectStatus(""), _connectType(""), _connectLength(0)
	{}

	void createRequest(const char *buffer);
	std::string getResponce();

	~HTTPRequest() = default;
};
