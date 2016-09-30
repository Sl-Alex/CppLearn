#include "chatserver.h"
#include <vector>

/// @todo Only for debugging, can be removed then
#include <iostream>
#include "chatconnection.h"

void serverTask(SOCKET listenSocket, std::atomic_bool &stop, std::atomic_bool &running, ConnectionManager &manager)
{
    int err = 0;
    int iResult = 0;

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    // Set non-blocking mode
    u_long mode = 1;
    ioctlsocket(listenSocket, FIONBIO, &mode);

    // Accept a client socket
    while (stop != true)
    {
        SOCKET newClientSocket = INVALID_SOCKET;

        // Non-blocking accept
        newClientSocket = accept(listenSocket, NULL, NULL);
        err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK)
        {
            Sleep(10);
            continue;
        }

        if (newClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return;
        }

        ChatConnection * newConnection = new ChatConnection();
        newConnection->start(newClientSocket);
        manager.addConnection(newConnection);
        manager.cleanup();
    }

    // Got a stop request, stop all connections
    manager.clear();

    // No longer need server socket
    closesocket(listenSocket);

    running = false;
}

ChatServer::ChatServer()
{
    // Default address is empty
    selfAddr.s_addr = 0;
    ListenSocket = INVALID_SOCKET;
    mStop = false;
    mRunning = false;
}

ChatServer::~ChatServer()
{
    stop();
}

bool ChatServer::init(void)
{
    ownAddr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    int iResult = getaddrinfo(NULL, "20000", &hints, &ownAddr);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        std::cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << std::endl;
        return false;
    }
//    std::cout << "Host name is " << ac << "." << std::endl;

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        std::cerr << "Yow! Bad host lookup." << std::endl;
        return false;
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        memcpy(&selfAddr, phe->h_addr_list[i], sizeof(struct in_addr));
        std::cout << "Address " << i << ": " << inet_ntoa(selfAddr) << std::endl;
        return true;
    }

    return false;
}

bool ChatServer::start(void)
{
    int iResult = 0;
    ListenSocket = INVALID_SOCKET;

    // Create a SOCKET for connecting to server
    ListenSocket = socket(ownAddr->ai_family, ownAddr->ai_socktype, ownAddr->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(ownAddr);
        WSACleanup();
        return 1;
    }
    // Setup the TCP listening socket
    iResult = bind( ListenSocket, ownAddr->ai_addr, (int)ownAddr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(ownAddr);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(ownAddr);

    mRunning = true;
    mStop = false;
    serverThread = std::thread(serverTask, ListenSocket, std::ref(mStop), std::ref(mRunning), std::ref(manager));

    return true;
}

void ChatServer::stop(void)
{
    mStop = true;
    if (serverThread.joinable())
        serverThread.join();

    mRunning = false;

    mStop = false;
}
