#include <string>
#include <map>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Request.hpp"
#include "Response.hpp"

#define BACKLOG 32
#define HTTP_REQUEST_BUFFER_SIZE 65536

#define HTTP_RESPONSE_STRING_200 "200 OK"
#define HTTP_RESPONSE_STRING_404 "404 Not Found"

struct RouteParams
{
    HTTPMethod method;
    Response (*functionPtr)(void);
};

class HTTPServer
{
private:
    int port;
    std::multimap<std::string, RouteParams> routes;

    int server_fd;
    int optval;
    sockaddr_in address;
    socklen_t addressLength;

    void serverSetup();
    Request readRequest(int socket);
    void sendResponse(int socket, Response &response);
    Response getResponseByRoute(std::string path, HTTPMethod method);
    RouteParams *findRouteParams(std::string path, HTTPMethod method);

public:
    HTTPServer(int port);
    void addRoute(HTTPMethod method, std::string route, Response (*functionPtr)(void));
    void serve();
};
