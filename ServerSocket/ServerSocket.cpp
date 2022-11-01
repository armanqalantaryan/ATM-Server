//
// Created by arman on 10/29/22.
//

#include "ServerSocket.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdexcept>


ServerSocket::ServerSocket(const int& _port)
    : m_serverSd(socket(AF_INET, SOCK_STREAM, 0))
{
    bzero((char*)&m_servAddr, sizeof(m_servAddr));
    m_servAddr.sin_family = AF_INET;
    m_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_servAddr.sin_port = htons(_port);
    initialize();
}

void ServerSocket::initialize()
{
    int rc;
    char* sql;
    rc = sqlite3_open("atm.db", &m_db);
    if(rc)
    {
       std::cerr << "Can`t open database "<< std::endl << sqlite3_errmsg(m_db);
    } else
     {
     std::cout << "Opened database successfully" << std::endl;
     }

    sql = "create table if not exists user("                    \
          " card_number BIGINT primary key not null,"           \
          " pin_code int not null,"                             \
          " balance int not null"                               \
          ");"

          "               insert into user (card_number,pin_code,balance)" \
          "             values (5510266988745563, 7860,561000);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7896632144785914, 9547,12000050);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7889965412233585, 8547,78500);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7889566221455895, 1114,754000);" \
          "               insert into user (card_number,pin_code,balance)" \
          "             values (7894555648897552, 5889,899600);";

sqlite3_exec(m_db,sql, nullptr,0,0);
}

void ServerSocket::closeSocket()
{
    close(m_clientSd);
    close(m_serverSd);
    sqlite3_close(m_db);
    std::cout << "Connection closed..." << std::endl;
}

void ServerSocket::startSession()
{

    //buffer to send and receive messages with
    int message = 1;

    if(m_serverSd < 0)
    {
        throw std::runtime_error("Error establishing the server socket");
    }
    //bind the socket to its local address
    int bindStatus = bind(m_serverSd, (struct sockaddr*) &m_servAddr,
                          sizeof(m_servAddr));
    if(bindStatus < 0)
    {
        throw std::runtime_error("Error binding socket to local address");

    }
    std::cout << "Waiting for a client to connect..." << std::endl;
    //listen for up to 5 requests at a time
    listen(m_serverSd, 5);

    sockaddr_in clientSockaddr_in;
    socklen_t clientSockAddrSize = sizeof(clientSockaddr_in);
    m_clientSd = accept(m_serverSd, (sockaddr *)&clientSockaddr_in, &clientSockAddrSize);
    if(m_clientSd < 0)
    {
        throw std::runtime_error("Error accepting request from client!");
    }
    std::cout << "Connected with client!" << std::endl;

    while(true)
    {
        //receive a message from the client (listen)
        std::cout << "Awaiting client response..." << std::endl;
        try {
            if (recv(m_clientSd, (void *) &message, sizeof(message), 0) < 0) {
                throw std::runtime_error("Error while receiving a message!");
            }
        }catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }
        //FIXME Needed to be improved
        if(message == 0)
        {
            std::cout << "Client has quit the session" << std::endl;
            break;
        }
        std::cout << "Client: " << message << std::endl;
        std::cout << ">";

        std::cin>>message;
        //send the message to client
        if(send(m_clientSd, (char*)&message, sizeof(message), 0) < 0)
        {
            throw std::runtime_error("Error while sending a message!");
        }
    }
    closeSocket();
}