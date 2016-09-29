#include "chatconnection.h"

static void connectionTask(SOCKET taskSocket, std::atomic_bool &stop, std::atomic_bool &running)
{
    char recvbuf[512];
    int recvbuflen = 512;

    int iResult = 0;

    bool isAlive = true;

    while (!stop && isAlive)
    {
        int err = 0;

        iResult = recv(taskSocket, recvbuf, recvbuflen, 0);
        err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK)
        {
            // Sleep for a while and then try to receive a new portion of data
            Sleep(10);
            continue;
        }

        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            int iSendResult;
            iSendResult = send(taskSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR)
            {
                err = WSAGetLastError();
                printf("send failed with error: %d\n", err);
                isAlive = false;
                continue;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
        {
            printf("Connection closing...\n");
            isAlive = false;
        }
        else
        {
            printf("recv failed with error: %d\n", err);
            isAlive = false;
        }
    }

    iResult = shutdown(taskSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        isAlive = false;
        closesocket(taskSocket);
        WSACleanup();
        running = false;
        return;
    }

    // cleanup
    closesocket(taskSocket);
    running = false;
}

ChatConnection::ChatConnection()
{
    mRunning = false;
    mStop = false;
    mSocket = INVALID_SOCKET;
}

ChatConnection::~ChatConnection()
{
    stop();
}

void ChatConnection::start(SOCKET newSocket)
{
    /// @todo Check mSocket against INVALID_SOCKET
    mSocket = newSocket;
    mRunning = true;
    mStop = false;

    mThread = std::thread(connectionTask,mSocket,std::ref(mStop), std::ref(mRunning));
}

void ChatConnection::stop(void)
{
    mStop = true;
    if (mThread.joinable())
        mThread.join();

    mStop = false;
    mRunning = false;
    mSocket = INVALID_SOCKET;
}
