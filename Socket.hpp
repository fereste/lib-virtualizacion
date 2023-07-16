#ifndef __LIB_SOCKET__
#define __LIB_SOCKET__

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class Socket
{
protected:
    int socketId;
    int port;
    int ipAddress;
    struct sockaddr_in config;
    bool isListening;

public:
    Socket()
    {
        isListening = false;

        memset(&config, '0', sizeof(config));
        config.sin_family = AF_INET;

        socketId = socket(AF_INET, SOCK_STREAM, 0);
    }

    Socket(int newSocketId, struct sockaddr_in *newSocketConfig)
    {
        socketId = newSocketId;
        isListening = false;
        if (newSocketConfig != NULL)
        {
            config = *newSocketConfig;
            port = newSocketConfig->sin_port;
            ipAddress = newSocketConfig->sin_addr.s_addr;
        }
    }

    ~Socket()
    {
        close(socketId);
    }

    struct sockaddr_in getConfig()
    {
        return config;
    }

    int startListening(const int port, const int maxQueue)
    {
        config.sin_addr.s_addr = htonl(INADDR_ANY);
        config.sin_port = htons(port);

        bind(socketId, (struct sockaddr *)&config, sizeof(config));

        int result = listen(socketId, maxQueue);
        isListening = !result;

        return result;
    }

    Socket acceptConnection(struct sockaddr *clientInformation)
    {
        int commSocketId = accept(socketId, clientInformation, NULL);
        return Socket(commSocketId, (struct sockaddr_in *)clientInformation);
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

    int receivePayload(char *buffer, size_t size)
    {
        int receivedBytes = read(socketId, buffer, size);
        buffer[receivedBytes] = 0;
        return receivedBytes;
    }

    int closeSocket()
    {
        return close(socketId);
    }

    int getSocketId()
    {
        return socketId;
    }
};

#endif
