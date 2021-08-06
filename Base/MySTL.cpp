#include "stdafx"
#include "MySTL.h"

template <typename T, int nQueueLen>
CycleQueue<T,nQueueLen>::CycleQueue()
{

}

bool push(T* pszData, size_t uDataLen);
bool pop(size_t uPopSize, T* pszData);
bool get(size_t uPopSize, T* pszData);
void clear();

private:
    bool pop(size_t uPopSize);