#ifndef _BASE_IJYBUFFER_H_
#define _BASE_IJYBUFFER_H_

#include <atomic>

struct IJYBuffer
{
    size_t GetSize() { return uDataLen; }
    void* GetData() { return (void*)byData; }

    void Init(size_t uSize) 
    {
        uDataLen = uSize; 
        uRef = 1;
    }

    void AddRef() { uRef++; }
    void DecRef() { uRef--; }
    uint16_t GetRef() { return uRef; }

private:
    std::atomic<uint16_t> uRef;
    size_t uDataLen;
    byte byData[];
};

static IJYBuffer* JYMemoryCreate(size_t uDataLen)
{
    IJYBuffer* pResult = NULL;

    pResult = (IJYBuffer*)malloc(uDataLen + sizeof(IJYBuffer));
    JYLOG_PROCESS_ERROR(pResult);

    pResult->Init(uDataLen);

Exit0:
    return pResult;
}

static void JYMemoryDelete(IJYBuffer* piBuffer)
{
    JY_PROCESS_ERROR(piBuffer);

    JY_PROCESS_ERROR(piBuffer->GetRef() > 0);

    piBuffer->DecRef();

    if (piBuffer->GetData() == 0)
    {
        free(piBuffer);
    }

    piBuffer = NULL;

    JY_STD_VOID_END
}

#endif