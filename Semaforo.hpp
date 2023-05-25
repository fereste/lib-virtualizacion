#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

class Semaforo
{
private:
    char *semaphoreName;
    sem_t *semaphore;

public:
    Semaforo(const char *name, const int initialValue)
    {
        semaphore = sem_open(name, O_CREAT, 0600, initialValue);
        semaphoreName = (char *)malloc(strlen(name) + 1);
        strcpy(semaphoreName, name);
    }

    ~Semaforo()
    {
        sem_close(semaphore);
        free(semaphoreName);
    }

    int getValue()
    {
        int value = 0;
        sem_getvalue(semaphore, &value);
        return value;
    }

    inline char *getName()
    {
        return semaphoreName;
    }

    inline sem_t *getSemaphore()
    {
        return semaphore;
    }

    inline void p()
    {
        sem_wait(semaphore);
    }

    inline void v()
    {
        sem_post(semaphore);
    }

    inline void destroy()
    {
        sem_close(semaphore);
        sem_unlink(semaphoreName);
    }
};
