#include "networking.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace networking {

void startServer(int port) {
    WSADATA wsaData;
    SOCKET serverSocket = INVALID_SOCKET, clientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "Server listening on port " << port << std::endl;

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    } else {
        std::cout << "Connection accepted." << std::endl;
    }

    // Placeholder for communication logic

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

void startClient(const char* host, int port) {
    WSADATA wsaData;
    SOCKET connectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, host, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(port);

    std::cout << "Client attempting to connect to " << host << ":" << port << std::endl;

    if (connect(connectSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return;
    } else {
        std::cout << "Connected to the server." << std::endl;
    }

    // Placeholder for communication logic

    closesocket(connectSocket);
    WSACleanup();
}

} // namespace networking
