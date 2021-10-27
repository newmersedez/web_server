#pragma once

#include <string>

class HTTPMessage
{
public:
	virtual void fill(char *buffer) = 0;
	virtual std::string get() = 0;
	virtual ~HTTPMessage() {}
};

class HTTPRequest : public HTTPMessage
{
private:
	std::string _method;
	std::string _version;
	std::string _host;

public:
	HTTPRequest() = default;

	void fill(char *buffer) override;
	std::string get() override;

	~HTTPRequest() = default;
};

class HTTPResponce : public HTTPMessage
{
private:

public:
	HTTPResponce() = default;

	void fill(char *buffer) override;
	std::string get() override;

	~HTTPResponce() = default;
};
