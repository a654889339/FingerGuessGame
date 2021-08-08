#ifndef _CYCLE_QUEUE_H_
#define _CYCLE_QUEUE_H_

template <typename T>
class CycleQueue
{
public:
    CycleQueue()
    {
        m_uBegin = 0;
        m_uEnd = 0;
        m_uQueueLen = 0;
        m_pQueue = NULL;
    }
    ~CycleQueue()
    {
        if (m_pQueue)
            delete m_pQueue;
    }

    bool init(size_t uQueueSize)
    {
        bool bResult = false;

        if (m_pQueue)
        {
            m_uQueueLen = 0;
            delete m_pQueue;
        }

        m_pQueue = new T[uQueueSize];
        JY_PROCESS_ERROR(m_pQueue);

        m_uQueueLen = uQueueSize;
        JY_STD_BOOL_END
    }

    bool push(T* pszData, size_t uDataLen)
    {
        bool bResult = false;
        size_t uEnd = 0;
        size_t uCopyNum = 0;

        JYLOG_PROCESS_ERROR(pszData);
        JYLOG_PROCESS_ERROR(uDataLen);
        JYLOG_PROCESS_ERROR(uDataLen + size() < m_uQueueLen);

        uEnd = min(m_uEnd + uDataLen, m_uQueueLen);
        uCopyNum = uEnd - m_uEnd;

        memcpy(m_pQueue + m_uEnd, pszData, sizeof(T) * uCopyNum);
        m_uEnd = (m_uEnd + uDataLen) % m_uQueueLen;

        uDataLen -= uCopyNum;
        JY_PROCESS_SUCCESS(uDataLen == 0);

        memcpy(m_pQueue, pszData + uCopyNum, sizeof(T) * uDataLen);

    Exit1:
        bResult = true;
    Exit0:
        return bResult;
    }

    bool pop(size_t uPopSize, T* pszData)
    {
        bool bResult = false;
        bool bRetCode = false;

        bRetCode = get(uPopSize, pszData);
        JYLOG_PROCESS_ERROR(bRetCode);

        bRetCode = pop(uPopSize);
        JYLOG_PROCESS_ERROR(bRetCode);

        bResult = true;
    Exit0:
        return bResult;
    }

    bool get(size_t uGetSize, T* pszData)
    {
        bool bResult = false;
        size_t uEnd = 0;
        size_t uCopyNum = 0;

        JYLOG_PROCESS_ERROR(pszData);
        JYLOG_PROCESS_ERROR(uGetSize);
        JYLOG_PROCESS_ERROR(uGetSize <= size());

        uEnd = min(m_uBegin + uGetSize, m_uQueueLen);
        uCopyNum = uEnd - m_uBegin;
        memcpy(pszData, m_pQueue + m_uBegin, sizeof(T) * uCopyNum);

        uGetSize -= uCopyNum;
        JY_PROCESS_SUCCESS(uGetSize == 0);

        memcpy(pszData + uCopyNum, m_pQueue, sizeof(T) * uGetSize);

    Exit1:
        bResult = true;
    Exit0:
        return bResult;
    }

    void clear()
    {
        m_uBegin = m_uEnd = 0;
    }

    size_t size()
    {
        return m_uBegin <= m_uEnd ? m_uEnd - m_uBegin : m_uQueueLen - m_uBegin + m_uEnd;
    }

    size_t res_size(){return m_uQueueLen - size() - 1;}

private:
    bool pop(size_t uPopSize)
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(uPopSize <= size());
        m_uBegin = (m_uBegin + uPopSize) % m_uQueueLen;

        bResult = true;
    Exit0:
        return bResult;
    };
    size_t m_uBegin;
    size_t m_uEnd;
    size_t m_uQueueLen;
    T* m_pQueue;
};


#endif
