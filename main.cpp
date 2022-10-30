//
// Created by arman on 10/8/22.
//

#include <stdexcept>
#include <iostream>

#include "ServerSocket/ServerSocket.h"

using namespace std;
//Server side
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Port is missing in arguments!" << std::endl;
    }
    const int port = atoi(argv[1]);
    ServerSocket serverSocket(port);
    try
    {
        serverSocket.startSession();
    }
    catch (std::runtime_error e)
    {
        std::cout << "Exited with error: ";
        std::cout << e.what() << std::endl;
    }
    return 0;
}