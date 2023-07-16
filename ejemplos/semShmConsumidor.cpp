#include "../MemoriaCompartida.hpp"
#include "../Semaforo.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
    cout << "Inicio" << endl;

    Semaforo s1("sem1", 1);
    Semaforo s2("sem2", 0);
    MemoriaCompartida<int> memoria("memoria", 200);

    while (true)
    {
        s2.p();
        cout << *(memoria.get()) << endl;
        memoria.set(200);
        s1.v();
    }

    return EXIT_SUCCESS;
}
