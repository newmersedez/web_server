#pragma once

#include <string>

class Client
{
private:
	std::string	_ip;
	std::string	_port;

public:
	Client() = default;

	Client(const std::string& ip, const std::string& port)
		: _ip(ip), _port(port)
	{}

	void setIp(const std::string& ip);
	void setPort(const std::string& port);

	const std::string& getIp() const;
	const std::string& getPort() const;

	~Client() = default;
};
