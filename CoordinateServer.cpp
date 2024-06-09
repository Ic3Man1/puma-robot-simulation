#include "CoordinateServer.h"
#include <iostream>

CoordinateServer::CoordinateServer(const char* port) : port(port), ListenSocket(INVALID_SOCKET), latestCoordinates(3, 0.0f) {}

CoordinateServer::~CoordinateServer() {
    closesocket(ListenSocket);
    WSACleanup();
    if (serverThreadHandle.joinable()) {
        serverThreadHandle.join();
    }
}

void CoordinateServer::start() {
    serverThreadHandle = std::thread(&CoordinateServer::serverThread, this);
}

std::vector<float> CoordinateServer::getCoordinates() {
    std::lock_guard<std::mutex> lock(coordMutex);
    return latestCoordinates;
}

void CoordinateServer::handleClient(SOCKET ClientSocket) {
    char recvbuf[12];  // 3 floats * 4 bytes each = 12 bytes
    int recvbuflen = 12;
    int iResult;

    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult == recvbuflen) {
            std::lock_guard<std::mutex> lock(coordMutex);
            memcpy(latestCoordinates.data(), recvbuf, recvbuflen);
            std::cout << "Received coordinates: "
                << latestCoordinates[0] << ", "
                << latestCoordinates[1] << ", "
                << latestCoordinates[2] << std::endl;
        }
        else if (iResult == 0) {
            std::cout << "Connection closing..." << std::endl;
        }
        else {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }
    } while (iResult > 0);

    closesocket(ClientSocket);
}

void CoordinateServer::serverThread() {
    WSADATA wsaData;
    int iResult;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    handleClient(ClientSocket);
}
