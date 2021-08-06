#ifndef _MYSTL_H_
#define _MYSTL_H_

template <typename T, size_t uQueueLen>
class CycleQueue
{
public:
    CycleQueue();

    bool push(T* pszData, size_t uDataLen);
    bool pop(size_t uPopSize, T* pszData);
    bool get(size_t uGetSize, T* pszData);
    void clear();
    size_t size();
    size_t res_size();

private:
    bool pop(size_t uPopSize);
    int m_nBegin;
    int m_nEnd;
    size_t m_uQueueLen;
    T m_Queue[uQueueLen];
};


#endif
