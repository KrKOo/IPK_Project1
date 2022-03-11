#include <string>
#include <stdexcept>
#define HTTP_METHOD_LENGTH 32
#define HTTP_ROUTE_LENGTH 256

enum HTTPMethod
{
	POST,
	GET,
	PUT,
	PATCH,
	DELETE
};

class Request
{
private:
	std::string body;
	std::string route;
	HTTPMethod method;
	void parseRequest();
	HTTPMethod getMethodFromString(std::string methodString);

public:
	Request(std::string body);
	std::string getRoute();
	HTTPMethod getMethod();
};
