#include "networking.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

namespace networking {

void initializeServer(int port) {
    WSADATA wsaData;
    SOCKET serverSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddress;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    listen(serverSocket, SOMAXCONN);

    std::cout << "Server is waiting for a connection on port " << port << "...\n";

    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "Client connected.\n";

    // Here you can communicate with the client

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

void connectToServer(const std::string& host, int port) {
    WSADATA wsaData;
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(host.c_str());

    clientService.sin_port = htons(port);

    if (connect(connectSocket, (struct sockaddr*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect.\n";
        closesocket(connectSocket);
        WSACleanup();
        return;
    }

    std::cout << "Connected to server.\n";

    // Here you can communicate with the server

    closesocket(connectSocket);
    WSACleanup();
}

} // namespace networking
