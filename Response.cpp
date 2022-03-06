#include "Response.hpp"
#include <sstream>

Response::Response(std::string code, std::string text)
{
	this->code = code;
	this->text = text;
	generateBody();
}

void Response::setCode(std::string code)
{
	this->code = code;
	generateBody();
}

void Response::setText(std::string text)
{
	this->text = text;
	generateBody();
}

const char *Response::getBody()
{
	return this->body.c_str();
}

size_t Response::length()
{
	return this->body.length();
}

void Response::generateBody()
{
	std::stringstream bodyStream;
	bodyStream << "HTTP/1.1 " << this->code << "\r\n"
			   << "Content-Type: text/plain\r\n"
			   << "Content-Length: " << this->text.length() << "\r\n"
			   << "\r\n"
			   << this->text;

	this->body = bodyStream.str();
}