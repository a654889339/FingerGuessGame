#ifndef _BASE_LOCK_QUEUE_H_
#define _BASE_LOCK_QUEUE_H_

#include <deque>
#include <mutex>
#include "IJYBuffer.h"

class LockQueue
{
public:
    bool Push(BYTE* pbyData, size_t uDataLen)
    {
        bool       bResult  = false;
        IJYBuffer* piBuffer = NULL;

        JYLOG_PROCESS_ERROR(pbyData);

        piBuffer = JYMemoryCreate(uDataLen);
        JYLOG_PROCESS_ERROR(piBuffer);

        memcpy(piBuffer->GetData(), pbyData, uDataLen);

        m_Mutex.lock();
        m_Queue.push_back(piBuffer);
        m_Mutex.unlock();

        JY_STD_BOOL_END
    }

    bool Pop(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen)
    {
        bool       bResult = false;
        IJYBuffer* piBuffer = NULL;

        JYLOG_PROCESS_ERROR(pbyData);

        m_Mutex.lock();

        if (!m_Queue.empty())
        {
            piBuffer = m_Queue.front();
            m_Queue.pop_front();
        }

        m_Mutex.unlock();

        JY_PROCESS_ERROR(piBuffer);

        JYLOG_PROCESS_ERROR(piBuffer->GetSize() <= uLimitSize);

        memcpy(pbyData, piBuffer->GetData(), piBuffer->GetSize());
        *puDataLen = piBuffer->GetSize();
        
        bResult = true;
    Exit0:
        if (!bResult)
        {
            JYMemoryDelete(piBuffer);
        }
        return bResult;
    }

    bool IsEmpty()
    {
        bool bResult = false;

        m_Mutex.lock();
        bResult = m_Queue.empty();
        m_Mutex.unlock();

        return bResult;
    }

private:
    std::deque<IJYBuffer*> m_Queue;
    std::mutex             m_Mutex;
};


#endif