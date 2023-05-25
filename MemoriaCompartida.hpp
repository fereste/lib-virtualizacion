#pragma once

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::string;

template <class T>
class MemoriaCompartida
{
private:
    string name;
    T *memoryPointer;

public:
    MemoriaCompartida(const string &name, int initialValue)
        : MemoriaCompartida(name.c_str(), initialValue)
    {
    }

    MemoriaCompartida(const char *name, int initialValue)
    {
        int memoryId = shm_open(name, O_CREAT | O_RDWR, 0600);
        ftruncate(memoryId, sizeof(T));
        memoryPointer = (T *)mmap(NULL, sizeof(T), PROT_READ | PROT_WRITE, MAP_SHARED, memoryId, 0);
        close(memoryId);
    }

    ~MemoriaCompartida()
    {
        munmap(memoryPointer, sizeof(T));
    }

    void destroy()
    {
        shm_unlink(name);
    }

    T *get()
    {
        return memoryPointer;
    }

    void set(T value)
    {
        *memoryPointer = value;
    }

    string getName()
    {
        return name;
    }
};
