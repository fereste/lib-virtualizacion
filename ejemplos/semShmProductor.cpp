#include "../MemoriaCompartida.hpp"
#include "../Semaforo.hpp"
#include <fcntl.h>
#include <iostream>
#include <semaphore.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

int main()
{
    cout << "Inicio" << endl;

    Semaforo s1("sem1", 1);
    Semaforo s2("sem2", 0);
    MemoriaCompartida<const char *> memoria("memoria", sizeof(char) * 5, "contenido2");

    memoria.destroy();

    return EXIT_SUCCESS;
}
