#ifndef NETWORKING_H
#define NETWORKING_H

namespace networking {
    void startServer(int port);
    void startClient(const char* host, int port);
}

#endif // NETWORKING_H
