#ifndef _JY_THREAD_H_
#define _JY_THREAD_H_

typedef void JYThreadFunction(void* pvArg);

#ifdef WIN32
#include "process.h"
#else
#include <unistd.h>
#include <pthread.h>
#endif

class JYThread
{
public:
    JYThread();
    ~JYThread();

    int             Create(JYThreadFunction* pfnThread, void* pvArg);
    int             Destroy();

    void            ThreadFunction();

private:
#ifdef WIN32
    HANDLE          m_ThreadHandle;
#else
    pthread_t       m_ThreadHandle;
#endif

    JYThreadFunction* m_pfnThread;
    void*             m_pvThreadArg;
};

static int JYThread_Sleep(unsigned uMilliseconds);

#endif