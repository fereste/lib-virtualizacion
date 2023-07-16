#include "../Socket.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main()
{
    Socket ls;
    ls.startListening(5001, 10);

    while (true)
    {
        Socket socketComunicacion = ls.acceptConnection(NULL);

        time_t ticks = time(NULL);
        char sendBuff[2000];
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));

        socketComunicacion.sendPayload(sendBuff);
        socketComunicacion.closeSocket();
    }

    return EXIT_SUCCESS;
}
