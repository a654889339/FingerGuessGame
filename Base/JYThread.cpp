#include "stdafx.h"
#include "JYThread.h"

JYThread::JYThread()
{
#ifdef WIN32
    m_ThreadHandle = NULL;
#else
    m_ThreadHandle = 0;
#endif
    m_pfnThread = NULL;
    m_pvThreadArg = NULL;
}

JYThread::~JYThread()
{
    Destroy();
}
#ifdef WIN32
static unsigned __stdcall MyThreadProc(void* pvArg)
#else
static void* MyThreadProc(void* pvArg)
#endif
{
    JYThread* pThread = (JYThread*)pvArg;

    pThread->ThreadFunction();

    return 0;
}

int JYThread::Create(JYThreadFunction* pfnThread, void* pvArg)
{
    m_pfnThread = pfnThread;
    m_pvThreadArg = pvArg;

    if (m_ThreadHandle)
        return false;

#ifdef WIN32
    unsigned uThreadID;
    m_ThreadHandle = (HANDLE)_beginthreadex(
        NULL,                    // SD
        0,                        // initial stack size
        MyThreadProc,            // thread function
        (void*)this,            // thread argument
        0,                        // creation option
        (unsigned*)&uThreadID   // thread identifier
    );
    return (m_ThreadHandle != NULL);
#else
    int nRetCode = -1;
    pthread_attr_t   ThreadAttr;
    nRetCode = pthread_attr_init(&ThreadAttr);
    if (nRetCode != 0)  // if fail
        return false;

    nRetCode = pthread_attr_setstacksize(&ThreadAttr, 4 * 1024 * 1024);
    if (nRetCode != 0)  // if fail
        return false;

    nRetCode = pthread_create(
        &m_ThreadHandle,
        &ThreadAttr,
        MyThreadProc,
        this
    );

    if (nRetCode != 0) // if fail
    {
        m_ThreadHandle = 0;
    }

    pthread_attr_destroy(&ThreadAttr);
    return (nRetCode == 0);
#endif
}

int JYThread::Destroy()
{
    int nResult = false;

    JY_PROCESS_ERROR(m_ThreadHandle);


#ifdef WIN32
    if (m_ThreadHandle)
    {
        WaitForSingleObject(m_ThreadHandle, INFINITE);

        CloseHandle(m_ThreadHandle);
#ifdef WIN32
        m_ThreadHandle = NULL;
#else
        m_ThreadHandle = 0;
#endif
    }
#else
    if (m_ThreadHandle)
    {
        pthread_join(m_ThreadHandle, NULL);
#ifdef WIN32
        m_ThreadHandle = NULL;
#else
        m_ThreadHandle = 0;
#endif
    }
#endif

    nResult = true;
Exit0:
    return nResult;
}

void JYThread::ThreadFunction()
{
    m_pfnThread(m_pvThreadArg);
}

int JYThread_Sleep(unsigned uMilliseconds)
{
#ifdef WIN32
    Sleep(uMilliseconds);
    return true;
#else
    int nRetCode = false;
    nRetCode = usleep(uMilliseconds * 1000);
    return (nRetCode == 0);
#endif
}
