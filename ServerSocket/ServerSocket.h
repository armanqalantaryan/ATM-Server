//
// Created by arman on 10/29/22.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>

class ServerSocket {
public:
    ServerSocket(const int&);
    void startSession();
private:
    void closeSocket();
    void initialize();

    sockaddr_in m_servAddr;
    const int m_serverSd;
    int m_clientSd;
    sqlite3* m_db;
};

#endif //SERVER_SOCKET_H
