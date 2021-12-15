#ifndef _CODE_STD_H_
#define _CODE_STD_H_

// 
typedef unsigned char      BYTE;
typedef unsigned char      uint8;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef char               int8;
typedef int                int32;
#ifdef _WIN32
typedef long long          int64;
#else
typedef long long int      int64;
#endif

// Function std
#define JY_STD_BOOL_END \
    bResult = true; \
Exit0: \
    return bResult;

#define JY_STD_BOOL_SUCCESS_END \
Exit1: \
    bResult = true; \
Exit0: \
    return bResult;

#define JY_STD_VOID_END \
Exit0: \
    return ;


// Process exception
#ifdef _MSC_VER
#define TEMP_DISABLE_WARNING(warningCode, expression)   \
        __pragma(warning(push))                             \
        __pragma(warning(disable:warningCode))              \
        expression                                          \
        __pragma(warning(pop))
#else
#define TEMP_DISABLE_WARNING(warningCode, expression)   \
        expression
#endif 

#define WHILE_FALSE_NO_WARNING  \
    TEMP_DISABLE_WARNING(4127, while (false))

#define JYLOG_PROCESS_ERROR(Condition) \
    do  \
    {   \
        if (!(Condition))       \
        {                       \
            printf(        \
                "JYLOG_PROCESS_ERROR(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
            );                  \
            goto Exit0;         \
        }                       \
    } WHILE_FALSE_NO_WARNING

#define JY_PROCESS_ERROR(Condition) \
    do  \
    {   \
        if (!(Condition))       \
            goto Exit0;         \
    } WHILE_FALSE_NO_WARNING

#define JY_PROCESS_ERROR_RET_CODE(Condition, Code) \
    do  \
    {   \
        if (!(Condition))       \
        {   \
            nResult = Code; \
            goto Exit0;         \
        } \
    } WHILE_FALSE_NO_WARNING

#define JY_PROCESS_SUCCESS(Condition) \
    do  \
    {   \
        if ((Condition))       \
            goto Exit1;         \
    } WHILE_FALSE_NO_WARNING

#define JY_TRUE_CONTINUE(Condition) \
        if ((Condition))       \
            continue;         \

#define JYLOG_PROCESS_CONTINUE(Condition) \
        if (!(Condition))       \
        {                       \
            printf(        \
                "JYLOG_PROCESS_CONTINUE(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
            );                  \
            continue;         \
        }                       \

#endif