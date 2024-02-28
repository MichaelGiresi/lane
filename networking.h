#ifndef NETWORKING_H
#define NETWORKING_H

#include <string>

namespace networking {
    void initializeServer(int port);
    void connectToServer(const std::string& host, int port);
}

#endif // NETWORKING_H
