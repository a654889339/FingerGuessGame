#ifndef _CYCLE_QUEUE_H_
#define _CYCLE_QUEUE_H_

template <typename T>
class CycleQueue
{
public:
    CycleQueue()
    {
        m_nBegin = 0;
        m_nEnd = 0;
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
        int nEnd = 0;
        int nCopyNum = 0;

        JYLOG_PROCESS_ERROR(pszData);
        JYLOG_PROCESS_ERROR(uDataLen);
        JYLOG_PROCESS_ERROR(uDataLen + size() < m_uQueueLen);

        nEnd = min(m_nEnd + uDataLen, m_uQueueLen);
        nCopyNum = nEnd - m_nEnd;

        memcpy(m_pQueue + m_nEnd, pszData, sizeof(T) * nCopyNum);
        m_nEnd = (m_nEnd + uDataLen) % m_uQueueLen;

        uDataLen -= nCopyNum;
        JY_PROCESS_SUCCESS(uDataLen == 0);

        memcpy(m_pQueue, pszData + nCopyNum, sizeof(T) * uDataLen);

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
        int nEnd = 0;
        int nCopyNum = 0;

        JYLOG_PROCESS_ERROR(pszData);
        JYLOG_PROCESS_ERROR(uGetSize);
        JYLOG_PROCESS_ERROR(uGetSize <= size());

        nEnd = min(m_nEnd + uGetSize, m_uQueueLen);
        nCopyNum = nEnd - m_nEnd;
        memcpy(pszData, m_pQueue + m_nEnd, sizeof(T) * nCopyNum);

        uGetSize -= nCopyNum;
        JY_PROCESS_SUCCESS(uGetSize == 0);

        memcpy(pszData + nCopyNum, m_pQueue, sizeof(T) * uGetSize);

    Exit1:
        bResult = true;
    Exit0:
        return bResult;
    }

    void clear()
    {
        m_nBegin = m_nEnd = 0;
    }

    size_t size()
    {
        return m_nBegin <= m_nEnd ? m_nEnd - m_nBegin : m_uQueueLen - m_nBegin + m_nEnd;
    }

    size_t res_size(){return m_uQueueLen - size() - 1;}

private:
    bool pop(size_t uPopSize)
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(uPopSize <= size());
        m_nEnd = (m_nEnd + uPopSize) % m_uQueueLen;

        bResult = true;
    Exit0:
        return bResult;
    };
    int m_nBegin;
    int m_nEnd;
    size_t m_uQueueLen;
    T* m_pQueue;
};


#endif
