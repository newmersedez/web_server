#pragma once

#include <string>

class Server
{
private:
	std::string	_ip;
	std::string	_port;
	std::string	_directory;

public:
	Server() = default;

	explicit Server(const std::string& ip, const std::string& port,
				const std::string& dir)
		: _ip(ip), _port(port), _directory(dir)
	{}
	
	void setIp(const std::string& ip);
	void setPort(const std::string& port);
	void setDirectory(const std::string& directory);

	const std::string& getIp() const;
	const std::string& getPort() const;
	const std::string& getDiretory() const;
	
	~Server() = default;
};
