#include "HTTPServer.hpp"

HTTPServer::HTTPServer(int port)
{
    this->port = port;

    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(this->port);

    this->addressLength = sizeof(this->address);

    serverSetup();
}

void HTTPServer::addRoute(HTTPMethod method, std::string path, Response (*functionPtr)(void))
{
    this->routes.insert({path, RouteParams{method, functionPtr}});
}

void HTTPServer::serve()
{
    int socket;
    while ((socket = accept(server_fd, (struct sockaddr *)&address, &addressLength)) >= 0)
    {
        Request request = readRequest(socket);

        Response response = getResponseByRoute(request.getPath(), request.getMethod());

        sendResponse(socket, response);

        shutdown(socket, SHUT_RDWR);
        close(socket);
    }

    if (socket < 0)
    {
        throw std::runtime_error("Socket Failure.");
    }
}

void HTTPServer::serverSetup()
{
    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        throw std::runtime_error("Socket failure.");
    }

    if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->optval, sizeof(this->optval)))
    {
        throw std::runtime_error("Socket failure.");
    }

    if (bind(this->server_fd, (struct sockaddr *)&(this->address), this->addressLength) < 0)
    {
        throw std::runtime_error("Bind failure.");
    }

    if (listen(this->server_fd, BACKLOG) < 0)
    {
        throw std::runtime_error("Listen failure.");
    }
}

Request HTTPServer::readRequest(int socket)
{
    char requestString[HTTP_REQUEST_BUFFER_SIZE];
    int bytesReceived = recv(socket, requestString, HTTP_REQUEST_BUFFER_SIZE - 1, 0);

    if (bytesReceived < 0)
    {
        throw std::runtime_error("Request receive failure.");
    }

    requestString[bytesReceived] = '\0';

    return Request(requestString);
}

void HTTPServer::sendResponse(int socket, Response &response)
{
    if (send(socket, response.getBody(), response.length(), 0) < 0)
    {
        throw std::runtime_error("Response Send Failure");
    }
}

Response HTTPServer::getResponseByRoute(std::string path, HTTPMethod method)
{
    RouteParams *routeParams = findRouteParams(path, method);
    if (routeParams == nullptr)
    {
        return Response(HTTP_RESPONSE_STRING_404);
    }

    return routeParams->functionPtr();
}

RouteParams *HTTPServer::findRouteParams(std::string path, HTTPMethod method)
{
    if (this->routes.find(path) == this->routes.end())
    {
        return nullptr;
    }

    for (auto it = this->routes.find(path); it != this->routes.upper_bound(path); ++it)
    {
        if (it->second.method == method)
        {
            return &it->second;
        }
    }

    return nullptr;
}