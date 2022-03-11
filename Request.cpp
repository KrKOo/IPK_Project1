#include "Request.hpp"

Request::Request(std::string body)
{
    this->body = body;
    parseRequest();
}

std::string Request::getRoute()
{
    return this->route;
}

HTTPMethod Request::getMethod()
{
    return this->method;
}

void Request::parseRequest()
{
    char method[HTTP_METHOD_LENGTH];
    char route[HTTP_ROUTE_LENGTH];
    int successfulScans = sscanf(this->body.c_str(), "%s %s %*s", method, route);

    if (successfulScans != 2)
    {
        throw std::runtime_error("Invalid Request Format.");
    }

    this->method = getMethodFromString(method);
    this->route = route;
}

HTTPMethod Request::getMethodFromString(std::string methodString)
{
    if (methodString == "GET")
    {
        return GET;
    }
    else if (methodString == "POST")
    {
        return POST;
    }
    else if (methodString == "PUT")
    {
        return PUT;
    }
    else if (methodString == "PATCH")
    {
        return PATCH;
    }
    else if (methodString == "DELETE")
    {
        return DELETE;
    }
    else
    {
        throw std::runtime_error("Invalid HTTP Method.");
    }
}
