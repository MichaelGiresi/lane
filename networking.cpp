#include "networking.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

void initializeNetwork() {
    bool debugEnabled = true; // Set to false to disable debug prints

    std::cout << "Initializing network..." << std::endl;
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        if (debugEnabled) {
    std::cout << "Debug message: ..." << std::endl;
}
        exit(EXIT_FAILURE);
    }

    SOCKET server_fd, new_socket; // Use SOCKET type instead of int for sockets.
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket failed with error: " << WSAGetLastError() << std::endl;
        if (debugEnabled) {
    std::cout << "Debug message: ..." << std::endl;
}
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    // Note: SO_REUSEADDR is usually sufficient on Windows.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        if (debugEnabled) {
    std::cout << "Debug message: ..." << std::endl;
}
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Use recv instead of read for Windows sockets
    int bytesReceived = recv(new_socket, buffer, 1024, 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    std::cout << "Message from client: " << buffer << std::endl;

    // Use send instead of write for Windows sockets
    int bytesSent = send(new_socket, hello, strlen(hello), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    std::cout << "Hello message sent!" << std::endl;

    closesocket(new_socket); // Use closesocket instead of close for Windows sockets.
    closesocket(server_fd);
    WSACleanup(); // Cleanup Winsock
    std::cout << "Network initialized successfully." << std::endl;
}
