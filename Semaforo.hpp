#pragma once

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

using std::string;

class Semaforo
{
private:
    sem_t *semaphore;
    string name;

public:
    Semaforo(const string name, const int initialValue) : Semaforo::Semaforo(name.c_str(), initialValue)
    {
    }

    Semaforo(const char *name, const int initialValue)
    {
        this->semaphore = sem_open(name, O_CREAT, 0600, 5);
        this->name = name;
    }

    ~Semaforo()
    {
        sem_close(semaphore);
    }

    int getValue()
    {
        int value = 0;
        sem_getvalue(semaphore, &value);
        return value;
    }

    string getName()
    {
        return name;
    }

    sem_t *getSemaphore()
    {
        return semaphore;
    }

    void p()
    {
        sem_wait(semaphore);
    }

    void v()
    {
        sem_post(semaphore);
    }

    void destroy()
    {
        sem_close(semaphore);
        sem_unlink(name.c_str());
    }
};
