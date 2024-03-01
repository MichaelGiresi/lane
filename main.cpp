#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include "networking.h"

int main() {
    int listenPort, targetPort;
    std::string targetAddress;

    // Welcome Message for LANE

    std::cout << "\n";
    std::cout << "\n";

    std::cout << R"(##      ####  ##  ## #####    #####  ##  ##    ##  ## ##### ######  ####   #### 
##     ##  ## ### ## ##       ##  ##  ####     ## ##  ##      ##   ##  ## ##    
##     ###### ## ### ####     #####    ##      ####   ####    ##   ##  ##  #### 
##     ##  ## ##  ## ##       ##  ##   ##      ## ##  ##      ##   ##  ##     ##
###### ##  ## ##  ## #####    #####    ##      ##  ## ##### ######  ####   #### )" << std::endl;
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Enter listen port number for this node: ";
    std::cin >> listenPort;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter target server address (IP) to connect to (or 'none' to skip): ";
    getline(std::cin, targetAddress);

    // Start the server in a separate thread
    std::thread serverThread(networking::startServer, listenPort);

    if (targetAddress != "none") {
        std::cout << "Enter target server port number to connect to: ";
        std::cin >> targetPort;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Give the server some time to start up
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Start the client in a separate thread only if a valid address is provided
        std::thread clientThread(networking::startClient, targetAddress.c_str(), targetPort);
        clientThread.join();
    }

    // Wait for the server thread to complete
    serverThread.join();

    return 0;
}
