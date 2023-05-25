#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

template <typename T>
class MemoriaCompartida
{
protected:
    char *memoryName;
    T *memoryPointer;
    unsigned long memorySize;

public:
    MemoriaCompartida(const char *name, const unsigned long size, const T initialValue)
    {
        int memoryId = shm_open(name, O_CREAT | O_RDWR, 0600);

        ftruncate(memoryId, size);
        memoryPointer = (T *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memoryId, 0);
        close(memoryId);

        *memoryPointer = initialValue;

        memorySize = size;
        memoryName = (char *)malloc(strlen(name) + 1);
        strcpy(memoryName, name);
    }

    ~MemoriaCompartida()
    {
        munmap(memoryPointer, memorySize);
        free(memoryName);
    }

    inline void destroy()
    {
        shm_unlink(memoryName);
    }

    inline T *get()
    {
        return memoryPointer;
    }

    inline void set(T value)
    {
        *memoryPointer = value;
    }

    inline char *getName()
    {
        return memoryName;
    }
};
