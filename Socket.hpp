#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class Socket
{
protected:
    int socketId;
    int port;
    int ipAddress;
    struct sockaddr_in config;

public:
    Socket()
    {
        memset(&config, '0', sizeof(config));
        config.sin_family = AF_INET;

        socketId = socket(AF_INET, SOCK_STREAM, 0);
    }

    Socket(int newSocketId, struct sockaddr_in *newSocketConfig)
    {
        socketId = newSocketId;
        // TODO: Configurar el socket.
    }

    ~Socket()
    {
        close(socketId);
    }

    struct sockaddr_in getConfig()
    {
        return config;
    }

    int startListening(const int port)
    {
        config.sin_addr.s_addr = htonl(INADDR_ANY);
        config.sin_port = htons(port);

        bind(socketId, (struct sockaddr *)&config, sizeof(config));

        return listen(socketId, 10);
    }

    Socket acceptConnection(struct sockaddr *clientInformation)
    {
        int commSocketId = accept(socketId, clientInformation, NULL);
        return Socket(commSocketId);
    }

    int connectToSocket(const char *ipAddress, const int port)
    {
        config.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress, &config.sin_addr);

        return connect(socketId, (struct sockaddr *)&config, sizeof(config));
    }

    int sendPayload(const char *payload)
    {
        return write(socketId, payload, strlen(payload));
    }

    int receivePayload(char *buffer)
    {
        int receivedCount = read(socketId, buffer, sizeof(buffer) - 1);
        buffer[receivedCount] = 0;

        return receivedCount;
    }

    int closeSocket()
    {
        close(socketId);
    }
};