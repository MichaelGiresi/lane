#include <iostream>
#include <string>
#include <limits> // Include for std::numeric_limits
#include "networking.h" // Make sure this includes both initializeServer and connectToServer functions

namespace {
void runServer(int port) {
    std::cout << "Starting server on port " << port << "...\n";
    networking::initializeServer(port);
    std::cout << "Server started. Press enter to exit.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void runClient(const std::string& host, int port) {
    std::cout << "Connecting to server " << host << " on port " << port << "...\n";
    networking::connectToServer(host, port);
    std::cout << "Connected to server. Press enter to exit.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
}

int main() {
    int port = 8080; // Default port
    std::string host = "127.0.0.1"; // Default host for client mode
    
    std::cout << "Select mode:\n";
    std::cout << "1. Server\n";
    std::cout << "2. Client\n";
    std::cout << "Enter choice (1 or 2): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Ignore newline character left in the input buffer

    switch (choice) {
        case 1:
            runServer(port);
            break;
        case 2:
            runClient(host, port);
            break;
        default:
            std::cerr << "Invalid choice. Exiting program.\n";
            return 1;
    }

    return 0;
}
