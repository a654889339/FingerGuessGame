#include "stdafx.h"
#include "MySTL.h"

template <typename T, size_t uQueueLen>
CycleQueue<T,uQueueLen>::CycleQueue()
{
    assert(uQueueLen);
    m_nBegin = 0;
    m_nEnd = 0;
    m_uQueueLen = uQueueLen;
}

template <typename T, size_t uQueueLen>
bool CycleQueue<T, uQueueLen>::push(T* pszData, size_t uDataLen)
{
    bool bResult = false;
    int nEnd = 0;
    int nCopyNum = 0;

    JYLOG_PROCESS_ERROR(pszData);
    JYLOG_PROCESS_ERROR(uDataLen);
    JYLOG_PROCESS_ERROR(uDataLen + size() < m_uQueueLen);

    nEnd = min(m_nEnd + uDataLen, m_uQueueLen);
    nCopyNum = nEnd - m_nEnd;

    memcpy(&m_Queue[m_nEnd], pszData, sizeof(T) * nCopyNum);
    m_nEnd = (m_nEnd + uDataLen) % m_uQueueLen;

    uDataLen -= nCopyNum;
    JY_PROCESS_SUCCESS(uDataLen == 0);

    memcpy(&m_Queue[0], pszData + nCopyNum, sizeof(T) * uDataLen);

Exit1:
    bResult = true;
Exit0:
    return bResult;
}

template <typename T, size_t uQueueLen>
bool CycleQueue<T, uQueueLen>::pop(size_t uPopSize, T* pszData)
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

template <typename T, size_t uQueueLen>
bool CycleQueue<T, uQueueLen>::get(size_t uGetSize, T* pszData)
{
    bool bResult = false;
    int nEnd = 0;
    int nCopyNum = 0;

    JYLOG_PROCESS_ERROR(pszData);
    JYLOG_PROCESS_ERROR(uGetSize);
    JYLOG_PROCESS_ERROR(uGetSize <= size());

    nEnd = min(m_nEnd + uGetSize, m_uQueueLen);
    nCopyNum = nEnd - m_nEnd;
    memcpy(pszData, &m_Queue[m_nEnd], sizeof(T) * nCopyNum);

    uGetSize -= nCopyNum;
    JY_PROCESS_SUCCESS(uGetSize == 0);

    memcpy(pszData + nCopyNum, &m_Queue[0], sizeof(T) * uGetSize);

Exit1:
    bResult = true;
Exit0:
    return bResult;
}

template <typename T, size_t uQueueLen>
void CycleQueue<T, uQueueLen>::clear()
{
    m_nBegin = m_nEnd = 0;
}

template <typename T, size_t uQueueLen>
size_t CycleQueue<T, uQueueLen>::size()
{
    return m_nEnd - m_nBegin;
}

template <typename T, size_t uQueueLen>
bool CycleQueue<T, uQueueLen>::pop(size_t uPopSize)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(uPopSize <= size());
    m_nEnd = (m_nEnd + uPopSize) % m_uQueueLen;

    bResult = true;
Exit0:
    return bResult;
}