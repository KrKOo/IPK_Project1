#include <iostream>
#include <string>

#include "HTTPServer.hpp"
#include "SysInfo.hpp"

#define MAX_PORT_NUMBER 65535

Response getHostnameResponse()
{
    std::string hostname = SysInfo::getHostname();
    return Response(HTTP_RESPONSE_STRING_200, hostname + "\n");
}
Response getCpuNameResponse()
{
    std::string cpuName = SysInfo::getCpuName();

    return Response(HTTP_RESPONSE_STRING_200, cpuName + "\n");
}

Response getLoadResponse()
{
    int cpuLoad = SysInfo::getCpuLoad();
    return Response(HTTP_RESPONSE_STRING_200, std::to_string(cpuLoad) + "%\n");
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (argc != 2)
    {
        std::cerr << "Port not defined." << std::endl;
        exit(EXIT_FAILURE);
    }

    char *endPtr = NULL;
    int port = strtol(argv[1], &endPtr, 10);
    if (*endPtr != 0 || port > MAX_PORT_NUMBER || port < 0)
    {
        std::cerr << "Invalid port." << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        HTTPServer httpServer(port);

        httpServer.addRoute(GET, "/hostname", getHostnameResponse);
        httpServer.addRoute(GET, "/cpu-name", getCpuNameResponse);
        httpServer.addRoute(GET, "/load", getLoadResponse);

        httpServer.serve();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}