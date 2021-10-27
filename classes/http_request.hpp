#pragma once

#include "server.hpp"
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>

class HTTPRequest
{
private:
	std::string	_method;
	std::string	_path;
	std::string	_version;
	std::string	_connectStatus;
	std::string	_connectType;
	size_t		_connectLength;

	std::string message404();
	std::string message200();

public:
	HTTPRequest()
		: _method(""), _path(""), _version(""),
		_connectStatus(""), _connectType(""), _connectLength(0)
	{}

	void createRequest(const char *buffer);
	std::string getResponce();

	~HTTPRequest() = default;
};
