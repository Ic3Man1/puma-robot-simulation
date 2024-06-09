#ifndef COORDINATE_SERVER_H
#define COORDINATE_SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

class CoordinateServer {
public:
    CoordinateServer(const char* port);
    ~CoordinateServer();
    void start();
    std::vector<float> getCoordinates();

private:
    void handleClient(SOCKET ClientSocket);
    void serverThread();

    std::vector<float> latestCoordinates;
    std::mutex coordMutex;
    SOCKET ListenSocket;
    const char* port;
    std::thread serverThreadHandle;
};

#endif // COORDINATE_SERVER_H
