#include "../Socket.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    Socket mySocket;
    int resultadoConexion = mySocket.connectToSocket("127.0.0.1", 5001);

    if (resultadoConexion < 0)
    {
        cout << "Error en la conexión" << endl;
        return EXIT_FAILURE;
    }

    char buffer[2000];
    int bytesRecibidos = 0;
    while ((bytesRecibidos = mySocket.receivePayload(buffer, sizeof(buffer) - 1)) > 0)
    {
        printf("%s\n", buffer);
    }

    mySocket.closeSocket();

    return EXIT_SUCCESS;
}
