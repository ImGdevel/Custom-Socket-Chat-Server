#ifndef REACTOR_H
#define REACTOR_H

#include <vector>
#include <functional>
#include <unordered_map>

class ClientSession;

class Reactor {
public:
    explicit Reactor(int port);
    ~Reactor();

    void start();
    void stop();

private:
    int port;
    int serverSocket;
    int epollFd;

    static const int MAX_EVENTS = 1024;

    bool running = false;
    
    void setupServerSocket();
    void setupIOMultiplexing();
    void acceptConnection();
    void handleClientEvent(int clientSocket);
    void setNonBlocking(int socket);

    std::unordered_map<int, ClientSession*> clientSessions;
};

#endif
