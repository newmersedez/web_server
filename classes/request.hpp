#pragma once

/* Using fabric method pattern for practice
	and also for another request/response models if needed*/

#include <string>
#include <sstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/* Abstact class of HTTP message(request and respond) */

class HTTPMessage
{
protected:
	std::stringstream	message;

public:
	virtual void initRequest(const char *buffer) = 0;
	virtual std::string getResponce(const std::string& dir) const = 0;
	virtual ~HTTPMessage() {};
};

/* HTTP Request/responce classes */

class HTTPRequest : public HTTPMessage
{
private:
	std::string _method;
	std::string _purpose;
	std::string _version;

private:
	std::string message200(const fs::path& path) const;
	std::string message404() const;

public:
	HTTPRequest() = default;

	void initRequest(const char *buffer) override;
	std::string getResponce(const std::string& dir) const override;

	~HTTPRequest() = default;
};

/* Creator with fabric method */

class HTTPRequestFabric
{
public:
	virtual ~HTTPRequestFabric() {};
	virtual HTTPRequest *factoryMethod() const = 0;
};

/* HTTP request/responce creators */

class HTTPRequestCreator : public HTTPRequestFabric
{
	HTTPRequest *factoryMethod() const override;
	~HTTPRequestCreator() = default;
};
